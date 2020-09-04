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
#define __MACO_simple_iterator_0_core(next, n, ud, g, f) __MACO_while(n)(next, (__MACO_prev(n), ud, g, f)) __MACO_compose(f, g, n, ud)
#define __MACO_simple_iterator_2_(n, ud, g, f) __MACO_simple_iterator_0_core(__MACO_simple_iterator_1_, n, ud, g, f)
#define __MACO_simple_iterator_1_(n, ud, g, f) __MACO_simple_iterator_0_core(__MACO_simple_iterator_2_, n, ud, g, f)
#define __MACO_simple_iterator_from_0(n, ud, g, f)  __MACO_loop(n, __MACO_simple_iterator_1_(__MACO_prev(n), ud, g, f))

#define __MACO_simple_repeat_from_0(n, f) __MACO_simple_iterator_from_0(n, __MACO_empty(), __MACO_1st, f)

#define __MACO_iterator_from_0_(n, ud, g, f, end_f) __MACO_simple_iterator_from_0(n, ud, g, f) __MACO_compose(end_f, g, n, ud)
#define __MACO_iterator_from_0(n, ud, g, f, end_f) __MACO_if(n)(__MACO_iterator_from_0_(__MACO_prev(n), ud, g, f, end_f),__MACO_empty())

#define __MACO_repeat_ud_from_0(n, ud, f, end_f) __MACO_iterator_from_0(n, ud, __MACO_1st, f, end_f)
#define __MACO_repeat_from_0(n, f, end_f) __MACO_iterator_from_0(n, __MACO_empty(), __MACO_1st, f, end_f)

#endif

#endif //MACO_ITERATOR_0_H
