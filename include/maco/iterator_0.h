//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_ITERATOR_0_H
#define MACO_ITERATOR_0_H

#include <maco/config.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeats_0.h>
#define __MACO_repeat_from_0(n, macro, end_macro) __MACO_repeat_0_##n (macro) __MACO_end_macro_0_##n(end_macro)
#define __MACO_simple_repeat_from_0(n, macro) __MACO_repeat_from_0(n, macro, macro)
#else
#include <maco/loop.h>
#define __MACO_simple_iterator_0_core(next, n, macro) __MACO_while(n)(next, (__MACO_prev(n), macro)) macro(n)
#define __MACO_simple_iterator_2_(n, macro) __MACO_simple_iterator_0_core(__MACO_simple_iterator_1_, n, macro)
#define __MACO_simple_iterator_1_(n, macro) __MACO_simple_iterator_0_core(__MACO_simple_iterator_2_, n, macro)
#define __MACO_simple_iterator_from_0(n, macro)  __MACO_loop(n, __MACO_simple_iterator_1_(__MACO_prev(n), macro))
#define __MACO_iterator_from_0_(n, macro, end_macro) __MACO_simple_iterator_from_0(n, macro) end_macro(n)
#define __MACO_iterator_from_0(n, macro, end_macro) __MACO_iterator_from_0_(__MACO_prev(n), macro, end_macro)

#endif

#endif //MACO_ITERATOR_0_H
