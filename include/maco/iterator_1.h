//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_ITERATOR_1_H
#define MACO_ITERATOR_1_H

#include <maco/config.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeats_1.h>
#define __MACO_iterator_from_1(n, macro, end_macro)   __MACO_repeat_1_##n (macro) __MACO_end_macro_1_##n(end_macro)
#define __MACO_simple_iterator_from_1(n, macro)       __MACO_iterator_from_1(n, macro, macro)
#else
#include <maco/loop.h>
#define __MACO_simple_iterator_1_core_(next, n, macro) __MACO_while(__MACO_prev(n))(next, (__MACO_prev(n), macro)) macro(n)
#define __MACO_simple_iterator_1_2_(n, macro)          __MACO_simple_iterator_1_core_(__MACO_simple_iterator_1_1_, n, macro)
#define __MACO_simple_iterator_1_1_(n, macro)          __MACO_simple_iterator_1_core_(__MACO_simple_iterator_1_2_, n, macro)
#define __MACO_simple_iterator_from_1(n, macro)        __MACO_loop(n, __MACO_simple_iterator_1_1_(n, macro))
#define __MACO_iterator_from_1(n, macro, end_macro)    __MACO_simple_iterator_from_1(__MACO_prev(n), macro) end_macro(n)
#endif

#endif //MACO_ITERATOR_1_H
