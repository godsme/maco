//
// Created by Darwin Yuan on 2020/9/12.
//

#ifndef MACO_META_DATA_COMMON_H
#define MACO_META_DATA_COMMON_H

#include <maco/basic.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace meta_data {
   template<typename T, typename = void>
   struct parameter_type_trait {
      using type = std::add_lvalue_reference_t<std::add_const_t<std::decay_t<T>>>;
   };

   template<typename T>
   constexpr bool should_pass_by_value =
      !std::is_array_v<T> &&
      (std::is_arithmetic_v<T> || std::is_pointer_v<T>) && sizeof(T) <= sizeof(void*);

   template<typename T>
   struct parameter_type_trait<T, std::enable_if_t<should_pass_by_value<std::decay_t<T>>>> {
      using type = std::decay_t<T>;
   };

   static constexpr auto flag_byte(size_t n) -> size_t {
      return n / 8;
   }

   static constexpr auto flag_mask(size_t n) -> uint8_t {
      return static_cast<uint8_t>(1 << (n % 8));
   }

   static constexpr auto clear_flag_mask(size_t n) -> uint8_t {
      return ~flag_mask(n);
   }

   template<typename F>
   constexpr static bool is_none_invokable = std::is_invocable_v<F>;

   template<typename F>
   using none_invoke_result_t = std::invoke_result_t<F>;
}

struct modify_meta{};

#define __Meta_ns NANO_CAF_NS::meta_data
#define __MeTa_var(x) __MACO_paste(__MACO_var_name(x), _)
#define __MeTa_byte(x) __MACO_paste(__MACO_var_name(x), _byte)
#define __MeTa_mask(x) __MACO_paste(__MACO_var_name(x), _mask)
#define __MeTa_clear_mask(x) __MACO_paste(__MACO_var_name(x), _clear_mask)
#define __Meta_present_name(x) __MACO_paste(__MACO_var_name(x), __present)
#define __Meta_modify_name(x) __MACO_paste(__MACO_var_name(x), __modify)

#endif //MACO_META_DATA_COMMON_H
