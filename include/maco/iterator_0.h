//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_ITERATOR_0_H
#define MACO_ITERATOR_0_H

#include <maco/config.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeats_0.h>
#define __MACO_repeat_from_0(n, f, end_f) __MACO_repeat_0_##n (f, __MACO_2nd, __MACO_empty()) __MACO_end_macro_0_##n(f, __MACO_2nd, __MACO_empty())
#define __MACO_simple_repeat_from_0(n, f) __MACO_repeat_from_0(n, f, f)
#define __MACO_repeat_ud_from_0(n, ud, f, end_f)  __MACO_repeat_0_##n (f, __MACO_keep__, ud) __MACO_end_macro_0_##n(f, __MACO_keep__, ud)
#else
#include <maco/detail/iterator_0.h>
#define __MACO_simple_repeat_from_0(n, f)        __MACO_simple_iterator_from_0_(n, __MACO_empty(), __MACO_2nd, f)
#define __MACO_repeat_ud_from_0(n, ud, f, end_f) __MACO_iterator_from_0_(n, ud, __MACO_keep__, f, end_f)
#define __MACO_repeat_from_0(n, f, end_f)        __MACO_iterator_from_0_(n, __MACO_empty(), __MACO_2nd, f, end_f)
#endif

#endif //MACO_ITERATOR_0_H
