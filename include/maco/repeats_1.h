//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_REPEATS_1_H
#define MACO_REPEATS_1_H

#if !defined(USING_EXPAND_REPEATS)
#define USING_EXPAND_REPEATS 1
#endif

#if USING_EXPAND_REPEATS
#include <maco/detail/repeats_1.h>
#define __MACO_repeat_from_1(n, macro, end_macro) __MACO_repeat_1_##n (macro) __MACO_end_macro_1_##n(end_macro)
#define __MACO_simple_repeat_from_1(n, macro) __MACO_repeat_from_1(n, macro, macro)
#else
#include <maco/loop.h>
#define __MACO_simple_repeat_1_2_(n, macro)    __MACO_while(__MACO_prev(n))(__MACO_simple_repeat_1_1_, (__MACO_prev(n), macro)) macro(n)
#define __MACO_simple_repeat_1_1_(n, macro)    __MACO_while(__MACO_prev(n))(__MACO_simple_repeat_1_2_,  (__MACO_prev(n), macro)) macro(n)
#define __MACO_simple_repeat_from_1(n, macro)  __MACO_eval(__MACO_simple_repeat_1_1_(n, macro))
#define __MACO_repeat_from_1(n, macro, end_macro) __MACO_simple_repeat_from_1(__MACO_prev(n), macro) end_macro(n)
#endif

#endif //MACO_REPEATS_1_H
