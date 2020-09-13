//
// Created by Darwin Yuan on 2020/9/12.
//

#ifndef MACO_RO_META_DATA_H
#define MACO_RO_META_DATA_H

#include <maco/map.h>
#include <maco/aggregate.h>
#include <maco/meta/meta_data_common.h>
#include <type_traits>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////
namespace ro_meta_data {

   template<typename T>
   struct meta_type_trait {
      using type = T;
      using element_type = T;
      using parameter_type = typename meta_data::parameter_type_trait<T>::type;
      using return_type = parameter_type;
      using value_type = T;

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_v<F, value_type>;

      template<typename F>
      constexpr static bool is_void_visitable = std::is_invocable_r_v<void, F, value_type>;

      template<typename F>
      using invoke_result_t = std::invoke_result_t<F, value_type>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_v<F, value_type&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         self = value;
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         return self;
      }

      template<typename F>
      inline constexpr static auto visit(parameter_type self, F&& f) {
         return f(self);
      }

      template<typename F>
      inline static auto modify(T& self, F&& f) -> void {
         f(self);
      }
   };

   template<typename C, size_t SIZE>
   struct meta_type_trait<C[SIZE]> {
      using type = C[SIZE];
      using element_type = C;
      using parameter_type = std::pair<C const*, size_t>;
      using return_type = parameter_type;

      using value_type = struct {
         type data_;
         size_t n_;
      };

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_v<F, const C*, size_t>;

      template<typename F>
      constexpr static bool is_void_visitable = std::is_invocable_r_v<void, F, const C*, size_t>;

      template<typename F>
      using invoke_result_t = std::invoke_result_t<F, const C*, size_t>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_v<F, C*&, size_t&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         auto [p, size] = value;
         auto total = std::min(SIZE, size);
         self.n_ = total;
         for(size_t i=0; i<total; i++) {
            self.data_[i] = p[i];
         }
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         return {self.data_, self.n_};
      }

      template<typename F>
      inline constexpr static auto visit(const value_type& self, F&& f)  {
         auto [p, size] = self;
         return f(p, size);
      }

      template<typename F>
      inline static auto modify(value_type& self, F&& f) -> void {
         auto& [p, size] = self;
         f(p, size);
      }
   };

   template<typename C>
   struct meta_type_trait<C[1]> : meta_type_trait<C> {};


   template<size_t N>
   struct meta_flags {
      enum { num_of_bytes = (N + 7) / 8 };
      unsigned char flags_[num_of_bytes]{};
   };

   template<typename F_SOME, typename F_NONE>
   constexpr bool same_result =
      std::is_same_v<
         typename meta_type_trait<F_SOME>::template invoke_result_t<F_SOME>,
         meta_data::none_invoke_result_t<F_NONE>>;
}

///////////////////////////////////////////////////////////////////////////////////////////////
#define __RO_Meta_ns NANO_CAF_NS::ro_meta_data
#define __RO_MeTa(x) __RO_Meta_ns::meta_type_trait<__MACO_var_type(x)>
#define __RO_Meta_value_type(x) typename __RO_MeTa(x)::value_type
#define __RO_Meta_result(x) typename __RO_MeTa(x)::return_type
#define __RO_Meta_para(x) typename __RO_MeTa(x)::parameter_type
#define __RO_Meta_elem(x) typename __RO_MeTa(x)::element_type

///////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_no_lock_meta_field__(n, x, set_visibility)                              \
private:                                                                              \
   constexpr static size_t  __MeTa_byte(x) = __Meta_ns::flag_byte(n);                 \
   constexpr static uint8_t __MeTa_mask(x) = __Meta_ns::flag_mask(n);                 \
private:                                                                              \
   __RO_Meta_value_type(x) __MeTa_var(x);                                             \
public:                                                                               \
   inline constexpr auto __MACO_var_name(x)() const noexcept -> __RO_Meta_result(x) {  \
       return __RO_MeTa(x)::get(__MeTa_var(x));                                       \
   }                                                                                  \
   template<typename F,                                                               \
            typename = std::enable_if_t<__RO_MeTa(x)::template is_void_visitable<F>>> \
   inline constexpr auto __MACO_var_name(x)(F&& f_some) const noexcept -> void {       \
       if(__Meta_present_name(x)())                                                   \
          __RO_MeTa(x)::visit(__MeTa_var(x), std::forward<F>(f_some));                \
   }                                                                                  \
   template<typename F_SOME, typename F_NONE,                                         \
            typename = std::enable_if_t<__RO_MeTa(x)::template is_visitable<F_SOME>>, \
            typename = std::enable_if_t<__Meta_ns::is_none_invokable<F_NONE>>,        \
            typename = std::enable_if_t<__RO_Meta_ns::same_result<F_SOME, F_NONE>>>   \
   inline constexpr                                                                   \
   auto __MACO_var_name(x)(F_SOME&& f_some, F_NONE&& f_none) const noexcept {          \
       if(__Meta_present_name(x)())                                                   \
          return __RO_MeTa(x)::visit(__MeTa_var(x), std::forward<F_SOME>(f_some));    \
       else                                                                           \
          return f_none();                                                            \
   }                                                                                  \
   inline constexpr auto __Meta_present_name(x)() const noexcept -> bool {            \
       return __secrete_ro_flags.flags_[__MeTa_byte(x)] & __MeTa_mask(x);             \
   }                                                                                  \
set_visibility:                                                                       \
   template<typename F,                                                               \
            typename = std::enable_if_t<__RO_MeTa(x)::template is_modifiable<F>>>     \
   inline auto __Meta_modify_name(x)(F&& modifier) noexcept -> void {                 \
      __RO_MeTa(x)::modify(__MeTa_var(x), std::forward<F>(modifier));                 \
      __secrete_ro_flags.flags_[__MeTa_byte(x)] |= __MeTa_mask(x);                    \
   }                                                                                  \
   template<size_t SIZE> inline                                                       \
   auto __MACO_var_name(x)(const __RO_Meta_elem(x) (&array)[SIZE]) noexcept -> void {  \
      __MACO_var_name(x)({array, SIZE});                                               \
   }                                                                                  \
   inline auto __MACO_var_name(x)(__RO_Meta_para(x) pair) noexcept -> void {           \
      __RO_MeTa(x)::set(__MeTa_var(x), pair);                                         \
      __secrete_ro_flags.flags_[__MeTa_byte(x)] |= __MeTa_mask(x);                    \
   }

///////////////////////////////////////////////////////////////////////////////////////
#define __CUB_ro_field__(n, x) __CUB_no_lock_meta_field__(n, x, protected)

///////////////////////////////////////////////////////////////////////////////////////
#define __CUB_ro_meta_data(...)                                                \
   __MACO_map_i(__CUB_ro_field__, __VA_ARGS__)                                 \
private:                                                                       \
   __RO_Meta_ns::meta_flags<__MACO_num_of_args(__VA_ARGS__)> __secrete_ro_flags

////////////////////////////////////////////////////////////////////////
#define __CUB_export_meta_w__(x)                  \
using __secrete_parent__::__Meta_modify_name(x);  \
using __secrete_parent__::__MACO_var_name(x);

////////////////////////////////////////////////////////////////////////
#define __CUB_2_stage_meta_table(rw_stage, ro_stage, ...)    \
struct ro_stage {                                            \
  __CUB_ro_meta_data(__VA_ARGS__);                           \
};                                                           \
template <typename RO = ro_stage>                            \
struct rw_stage : RO {                                       \
private:                                                     \
  using __secrete_parent__ = RO;                             \
public:                                                      \
  __MACO_map(__CUB_export_meta_w__, __VA_ARGS__);            \
}

#endif //MACO_RO_META_DATA_H
