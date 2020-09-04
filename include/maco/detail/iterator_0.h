//
// Created by Darwin Yuan on 2020/9/4.
//

#ifndef MACO_DETAIL_ITERATOR_0_H
#define MACO_DETAIL_ITERATOR_0_H

#include <maco/loop.h>
#define __MACO_simple_iterator_0_core(next, n, ud, g, f) __MACO_while(n)(next, (__MACO_prev(n), ud, g, f)) __MACO_compose(f, g, ud, n)
#define __MACO_simple_iterator_2_(n, ud, g, f) __MACO_simple_iterator_0_core(__MACO_simple_iterator_1_, n, ud, g, f)
#define __MACO_simple_iterator_1_(n, ud, g, f) __MACO_simple_iterator_0_core(__MACO_simple_iterator_2_, n, ud, g, f)
#define __MACO_simple_iterator_from_0_(n, ud, g, f)  __MACO_loop(n, __MACO_simple_iterator_1_(__MACO_prev(n), ud, g, f))

#define __MACO_iterator_from_0__(n, ud, g, f, end_f) __MACO_simple_iterator_from_0_(n, ud, g, f) __MACO_compose(end_f, g, ud, n)
#define __MACO_iterator_from_0_(n, ud, g, f, end_f) __MACO_if(n)(__MACO_iterator_from_0__(__MACO_prev(n), ud, g, f, end_f),__MACO_empty())

#endif //MACO_DETAIL_ITERATOR_0_H
