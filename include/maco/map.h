//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_MAP_H
#define MACO_MAP_H

#include <maco/config.h>
#include <maco/parameter.h>
#include <maco/detail/int_succ.h>
#include <maco/loop.h>
#include <maco/natural.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeat_call.h>
#define __MACO_map(f, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (f, 0, __VA_ARGS__)
#else
#define __MACO_map_core_(next, f, m, n, x, ...)   f(m, x) __MACO_while(__MACO_dec(n))(next, (f, __MACO_inc(m), __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_2__(f, m, n, x, ...)           __MACO_map_core_(__MACO_map_1__, f, m, n, x, __VA_ARGS__)
#define __MACO_map_1__(f, m, n, x, ...)           __MACO_map_core_(__MACO_map_2__, f, m, n, x, __VA_ARGS__)
#define __MACO_map_(f, n, ...)                    __MACO_loop(n, __MACO_map_1__(f, 0, n, __VA_ARGS__))
#define __MACO_map(f, ...)                        __MACO_map_(f, __MACO_num_of_args(__VA_ARGS__), __VA_ARGS__)
#endif

#endif //MACO_MAP_H
