//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_FOREACH_H
#define MACO_FOREACH_H

#include <maco/config.h>
#include <maco/pp_size.h>
#include <maco/detail/int_succ.h>
#include <maco/loop.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeat_call.h>
#define __MACO_foreach(macro, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (macro, 0, __VA_ARGS__)
#else
#define __MACO_foreach_core_(next, macro, m, n, x, ...) macro(m, x) __MACO_while(__MACO_prev(n))(next, (macro, __MACO_succ(m), __MACO_prev(n), __VA_ARGS__))
#define __MACO_foreach_2_(macro, m, n, x, ...)  __MACO_foreach_core_(__MACO_foreach_1_, macro, m, n, x, __VA_ARGS__)
#define __MACO_foreach_1_(macro, m, n, x, ...)  __MACO_foreach_core_(__MACO_foreach_2_, macro, m, n, x, __VA_ARGS__)

// only if the size of list is greater than 0, we do the real recursion, otherwise we quite early.
#define __MACO_foreach_(macro, n, ...)          __MACO_loop(n, __MACO_foreach_1_(macro, 0, n, __VA_ARGS__))
#define __MACO_foreach(macro, ...)              __MACO_foreach_(macro, __MACO_pp_size(__VA_ARGS__), __VA_ARGS__)
#endif

#endif //MACO_FOREACH_H
