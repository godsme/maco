//
// Created by Darwin Yuan on 2020/9/12.
//

#ifndef MACO_LOCK_META_DATA_H
#define MACO_LOCK_META_DATA_H

#include <maco/basic.h>
#include <maco/map.h>
#include <maco/aggregate.h>
#include <maco/meta/meta_data_common.h>
#include <type_traits>
#include <algorithm>
#include <mutex>
#include <shared_mutex>
#include <atomic>

///////////////////////////////////////////////////////////////////////////////////////////////

namespace lock_meta_data {

   template<typename T, typename = void>
   struct meta_type_trait {
      using type = T;
      using element_type = T;
      using parameter_type = typename meta_data::parameter_type_trait<T>::type;
      using return_type = std::decay_t<T>;
      using value_type = struct {
         mutable std::shared_mutex mutex_;
         T value;
      };

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_v<F, parameter_type>;

      template<typename F>
      using invoke_result_t = std::invoke_result_t<F, parameter_type>;

      template<typename F>
      constexpr static bool is_void_visitable = std::is_invocable_r_v<void, F, parameter_type>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_v<F, T&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         std::unique_lock lock(self.mutex_);
         self = value;
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         std::shared_lock lock(self.mutex_);
         return self;
      }

      template<typename F>
      inline static auto visit(parameter_type self, F&& f) {
         std::shared_lock lock(self.mutex_);
         return f(self);
      }

      template<typename F>
      inline static auto modify(T& self, F&& f) -> void {
         std::unique_lock lock(self.mutex_);
         f(self);
      }
   };

   template<typename T>
   struct meta_type_trait<T, std::enable_if_t<meta_data::should_pass_by_value<T>>> {
   using type = T;
   using element_type = T;
   using parameter_type = typename meta_data::parameter_type_trait<T>::type;
   using return_type = std::decay_t<T>;
   using value_type = std::atomic<T>;

   template<typename F>
   constexpr static bool is_visitable = std::is_invocable_v<F, const T>;

   template<typename F>
   using invoke_result_t = std::invoke_result_t<F, const T>;

   template<typename F>
   constexpr static bool is_void_visitable = std::is_invocable_r_v<void, F, const T>;

   template<typename F>
   constexpr static bool is_modifiable = std::is_invocable_v<F, T&>;

   inline constexpr static auto set(value_type& self, parameter_type value) -> void {
      self.store(value, std::memory_order_relaxed);
   }

   inline constexpr static auto get(const value_type& self) -> return_type {
      return self.load(std::memory_order_relaxed);
   }

   template<typename F>
   inline static auto visit(const value_type& self, F&& f) {
      return f(self.load(std::memory_order_relaxed));
   }

   // probably has a problem
   template<typename F>
   inline static auto modify(value_type& self, F&& f) -> void {
      auto value = self.load(std::memory_order_relaxed);
      f(value);
      self.store(value, std::memory_order_relaxed);
   }
};

template<typename C, size_t SIZE>
struct meta_type_trait<C[SIZE], void> {
   using type = C[SIZE];
   using element_type = C;
   using parameter_type = std::pair<C const*, size_t>;
   using return_type = std::pair<type, size_t>;

   using value_type = struct {
      mutable std::shared_mutex mutex_;
      struct {
         type data_;
         size_t n_;
      }v_;
   };

   template<typename F>
   constexpr static bool is_visitable = std::is_invocable_v<F, const C*, size_t>;

   template<typename F>
   using invoke_result_t = std::invoke_result_t<F, const C*, size_t>;

   template<typename F>
   constexpr static bool is_void_visitable = std::is_invocable_r_v<void, F, const C*, size_t>;

   template<typename F>
   constexpr static bool is_modifiable = std::is_invocable_r_v<void, F, C*&, size_t&>;

   inline constexpr static auto set(value_type& self, parameter_type value) -> void {
      std::unique_lock lock(self.mutex_);
      auto [p, size] = value;
      auto total = std::min(SIZE, size);
      self.v_.n_ = total;
      for(size_t i=0; i<total; i++) {
         self.v_.data_[i] = p[i];
      }
   }

   inline constexpr static auto get(const value_type& self) -> return_type {
      std::shared_lock lock(self.mutex_);
      return_type result;
      auto size = self.v_.n_;
      auto& data = self.v_.data_;
      for(size_t i=0; i<size; i++)
         result.first[i] = data[i];
      result.second = size;
      return result;
   }

   template<typename F>
   inline static auto visit(const value_type& self, F&& f) {
      std::shared_lock lock(self.mutex_);
      auto [p, size] = self.v_;
      return f(p, size);
   }

   template<typename F>
   inline static auto modify(value_type& self, F&& f) -> void {
      std::unique_lock lock(self.mutex_);
      auto& [p, size] = self.v_;
      f(p, size);
   }
};

template<typename C>
struct meta_type_trait<C[1]> : meta_type_trait<C> {};

template<typename F>
constexpr static bool is_none_invokable = std::is_invocable_r_v<void, F>;

template<typename F_SOME, typename F_NONE>
constexpr bool same_result =
   std::is_same_v<
      typename meta_type_trait<F_SOME>::template invoke_result_t<F_SOME>,
      meta_data::none_invoke_result_t<F_NONE>>;

template<size_t N>
struct meta_flags {
   enum { num_of_bytes = (N + 7) / 8 };
   std::atomic<unsigned char> v_[num_of_bytes]{};
};
}

///////////////////////////////////////////////////////////////////////////////////////////////
#define __Lock_Meta_ns NANO_CAF_NS::lock_meta_data
#define __Lock_MeTa(x) __Lock_Meta_ns::meta_type_trait<__MACO_var_type(x)>
#define __Lock_Meta_value_type(x) typename __Lock_MeTa(x)::value_type
#define __Lock_Meta_result(x) typename __Lock_MeTa(x)::return_type
#define __Lock_Meta_para(x) typename __Lock_MeTa(x)::parameter_type
#define __Lock_Meta_elem(x) typename __Lock_MeTa(x)::element_type
#define __Lock_Meta_set_flag(x) __MACO_paste(__MACO_var_name(x), _set_flag)
#define __Lock_Meta_clear(x) __MACO_paste(clear_, __MACO_var_name(x))
///////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_lock_meta_field__(n, x)                                                       \
private:                                                                                    \
   constexpr static size_t  __MeTa_byte(x)       = __Meta_ns::flag_byte(n);                 \
   constexpr static uint8_t __MeTa_mask(x)       = __Meta_ns::flag_mask(n);                 \
   constexpr static uint8_t __MeTa_clear_mask(x) = __Meta_ns::clear_flag_mask(n);           \
private:                                                                                    \
   __Lock_Meta_value_type(x) __MeTa_var(x);                                                 \
private:                                                                                    \
   inline auto __Lock_Meta_set_flag(x)() noexcept -> void {                                 \
      auto flags = __secrete_lk_flags.v_[__MeTa_byte(x)].load(std::memory_order_relaxed);   \
      uint8_t new_flags;                                                                    \
      do {                                                                                  \
         if(__unlikely(flags & __MeTa_mask(x))) break;                                      \
         new_flags = flags | __MeTa_mask(x);                                                \
      } while(!__secrete_lk_flags.v_[__MeTa_byte(x)]                                        \
                  .compare_exchange_strong(flags, new_flags,                                \
                      std::memory_order_release, std::memory_order_relaxed));               \
   }                                                                                        \
public:                                                                                     \
   inline auto __Lock_Meta_clear(x)() noexcept -> void {                                    \
      auto flags = __secrete_lk_flags.v_[__MeTa_byte(x)].load(std::memory_order_relaxed);   \
      uint8_t new_flags;                                                                    \
      do {                                                                                  \
         if(__unlikely((flags | __MeTa_mask(x)) == 0)) break;                               \
         new_flags = flags & __MeTa_clear_mask(x);                                          \
      } while(!__secrete_lk_flags.v_[__MeTa_byte(x)]                                        \
                  .compare_exchange_strong(flags, new_flags,                                \
                              std::memory_order_release, std::memory_order_relaxed));       \
   }                                                                                        \
   inline auto __MACO_var_name(x)() const noexcept -> __Lock_Meta_result(x) {                \
       return __Lock_MeTa(x)::get(__MeTa_var(x));                                           \
   }                                                                                        \
   inline auto __Meta_present_name(x)() const noexcept -> bool {                            \
       return __MeTa_mask(x) &                                                              \
          __secrete_lk_flags.v_[__MeTa_byte(x)].load(std::memory_order_acquire);            \
   }                                                                                        \
   template<typename F,                                                                     \
            typename = std::enable_if_t<__Lock_MeTa(x)::template is_void_visitable<F>>>     \
   inline auto __MACO_var_name(x)(F&& f_some) const noexcept -> void {                       \
       if(__Meta_present_name(x)())                                                         \
          __Lock_MeTa(x)::visit(__MeTa_var(x), std::forward<F>(f_some));                    \
   }                                                                                        \
   template<typename F_SOME, typename F_NONE,                                               \
            typename = std::enable_if_t<__Lock_MeTa(x)::template is_visitable<F_SOME>>,     \
            typename = std::enable_if_t<__Meta_ns::is_none_invokable<F_NONE>>,              \
            typename = std::enable_if_t<__Lock_Meta_ns::same_result<F_SOME, F_NONE>>>       \
   inline auto __MACO_var_name(x)(F_SOME&& f_some, F_NONE&& f_none) const noexcept {         \
       if(__Meta_present_name(x)())                                                         \
          return __Lock_MeTa(x)::visit(__MeTa_var(x), std::forward<F_SOME>(f_some));        \
       else                                                                                 \
          return f_none();                                                                  \
   }                                                                                        \
   template<typename F,                                                                     \
            typename = std::enable_if_t<__Lock_MeTa(x)::template is_modifiable<F>>>         \
   inline auto __Meta_modify_name(x)(F&& f_modifier) noexcept -> void {                     \
      __Lock_MeTa(x)::modify(__MeTa_var(x), std::forward<F>(f_modifier));                   \
      __Lock_Meta_set_flag(x)();                                                            \
   }                                                                                        \
   template<size_t I>                                                                       \
   inline auto __MACO_var_name(x)(const __Lock_Meta_elem(x) (&array)[I]) noexcept -> void {  \
      __MACO_var_name(x)({array, I});                                                        \
   }                                                                                        \
   inline auto __MACO_var_name(x)(__Lock_Meta_para(x) pair) noexcept -> void {               \
      __Lock_MeTa(x)::set(__MeTa_var(x), pair);                                             \
      __Lock_Meta_set_flag(x)();                                                            \
   }


///////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_lock_meta_data(...)                                                \
   __MACO_map_i(__CUB_lock_meta_field__, __VA_ARGS__)                            \
private:                                                                         \
   __Lock_Meta_ns::meta_flags<__MACO_num_of_args(__VA_ARGS__)> __secrete_lk_flags

///////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_lock_meta_table(name, ...)       \
struct name { __CUB_lock_meta_data(__VA_ARGS__); }

#endif //MACO_LOCK_META_DATA_H
