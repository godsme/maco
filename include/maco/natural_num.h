//
// Created by Darwin Yuan on 2020/9/3.
//

#ifndef MACO_NATURAL_NUM_H
#define MACO_NATURAL_NUM_H

#include <maco/basic.h>
#include <maco/loop.h>
#include <maco/detail/int_succ.h>
#include <maco/detail/int_prev.h>
#include <maco/condition.h>

#define __MACO_loop_return__(macro, ...)   __MACO_1st __VA_ARGS__
#define __MACO_loop_r_1__(n)             __MACO_if(__MACO_prev(n))(__MACO_continue__, __MACO_loop_return__)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define __MACO_natural_sub_2(m, n)     __MACO_loop_r_1__(n)(__MACO_natural_sub_1, (__MACO_dec(m), __MACO_dec(n)))
#define __MACO_natural_sub_1(m, n)     __MACO_loop_r_1__(n)(__MACO_natural_sub_2, (__MACO_dec(m), __MACO_dec(n)))
#define __MACO_sub(m, n)               __MACO_loop(n, __MACO_natural_sub_1(m, n))

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define __MACO_natural_add_2(m, n)     __MACO_loop_r_1__(n)(__MACO_natural_add_1, (__MACO_inc(m), __MACO_dec(n)))
#define __MACO_natural_add_1(m, n)     __MACO_loop_r_1__(n)(__MACO_natural_add_2, (__MACO_inc(m), __MACO_dec(n)))
#define __MACO_add(m, n)               __MACO_loop(n, __MACO_natural_add_1(m, n))

#define __MACO_eq(m, n)                __MACO_not(__MACO_sub(m, n))
#define __MACO_neq(m, n)               __MACO_bool(__MACO_sub(m, n))
#define __MACO_gt(m, n)                __MACO_gt_0(__MACO_sub(m, n))
#define __MACO_lt(m, n)                __MACO_gt_0(__MACO_sub(n, m))
#define __MACO_gte(m, n)               __MACO_gte_0(__MACO_sub(m, n))
#define __MACO_lte(m, n)               __MACO_gte_0(__MACO_sub(n, m))

#endif //MACO_NATURAL_NUM_H
