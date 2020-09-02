//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_REPEATS_1_H
#define MACO_REPEATS_1_H

#if USING_EXPAND_REPEATS
#include <maco/detail/repeats_1.h>
#define __MACO_repeat_from_1(n, macro, end_macro) __MACO_repeat_1_##n (macro) __MACO_end_macro_1_##n(end_macro)
#define __MACO_simple_repeat_from_1(n, macro) __MACO_repeat_from_1(n, macro, macro)
#else
#include <maco/loop.h>
#define __MACO_simple_repeat_from_1_(n, macro) __MACO_when(n)(__MACO_simple_repeat_from_1_(__MACO_prev(n), macro)) macro(n)
#define __MACO_simple_repeat_from_1(n, macro) __MACO_eval(__MACO_simple_repeat_from_1_(n, macro))
#endif

#endif //MACO_REPEATS_1_H
