//
// Created by Darwin Yuan on 2020/8/30.
//

#include <catch.hpp>
#include <maco/repeat_call.h>
#include <maco/aggregate.h>

namespace {
   TEST_CASE("stringify") {
      REQUIRE(std::string("abcd123") == __MACO_stringify(abcd123));
   }

   constexpr int ab_cd = 10;
   TEST_CASE("concat") {
      static_assert(ab_cd == __MACO_concat(ab, _cd));
   }

#define __succ_0 1
#define __succ_1 2
#define __succ_2 3

#define __succ(n) __MACO_concat(__succ_, n)

#define __r(n, x) __MACO_concat(x, n)

   TEST_CASE("succ") {
      static_assert(1 == __succ(0));
      static_assert(2 == __succ(1));
      static_assert(3 == __succ(2));
   }

#define num_macro(n, x) , n + x

#define __num(...) __MACO_foreach(num_macro, __VA_ARGS__)

constexpr int my_array[4] = {0  __num(1,2,3)};

   TEST_CASE("repeat call + succ") {
      REQUIRE(my_array[1] == 1);
      REQUIRE(my_array[2] == 3);
      REQUIRE(my_array[3] == 5);
   }

}