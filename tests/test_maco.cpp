//
// Created by Darwin Yuan on 2020/8/30.
//

#include <catch.hpp>
#include <maco/foreach.h>
#include <maco/repeats_0.h>
#include <maco/repeats_1.h>
#include <maco/condition.h>
#include <maco/loop.h>
#include <maco/detail/int_prev.h>
#include <maco/natural_num.h>

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
constexpr int array4[] = { __num() };

   TEST_CASE("repeat call + succ") {
      REQUIRE(my_array[1] == 1);
      REQUIRE(my_array[2] == 3);
      REQUIRE(my_array[3] == 5);
      REQUIRE(sizeof(array4) == 0);
   }

#define num_plus(n) 10 + n ,
#define num_last(n) 10 + n

   constexpr int array0[] = { __MACO_repeat_from_0(3, num_plus, num_last) };

   TEST_CASE("repeat from 0") {
      REQUIRE(array0[0] == 10);
      REQUIRE(array0[1] == 11);
      REQUIRE(array0[2] == 12);
   }

   constexpr int array00[] = { __MACO_simple_repeat_from_0(3, num_plus) 0 };

   TEST_CASE("simple repeat from 0") {
      REQUIRE(array00[0] == 10);
      REQUIRE(array00[1] == 11);
      REQUIRE(array00[2] == 12);
   }

   constexpr int array1[] = { __MACO_repeat_from_1(3, num_plus, num_last) };

   TEST_CASE("repeat from 1") {
      REQUIRE(array1[0] == 11);
      REQUIRE(array1[1] == 12);
      REQUIRE(array1[2] == 13);
   }

   constexpr int array11[] = { __MACO_simple_repeat_from_1(3, num_plus) 0 };

   TEST_CASE("simple repeat from 1") {
      REQUIRE(array11[0] == 11);
      REQUIRE(array11[1] == 12);
      REQUIRE(array11[2] == 13);
   }

#define m(n) 1 + n ,
#define m_end(n) 1 + n

//#define repeat(f, n) repeat(f, prev(n)) , f(n)
   constexpr int array3[] = { __MACO_repeat_from_1(3, m, m_end) };



}