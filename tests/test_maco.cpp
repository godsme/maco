//
// Created by Darwin Yuan on 2020/8/30.
//

#include <catch.hpp>
#include <maco/basic.h>

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

   TEST_CASE("succ") {
      static_assert(1 == __succ(0));
      static_assert(2 == __succ(1));
      static_assert(3 == __succ(2));
   }

}