//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_MAP_H
#define MACO_MAP_H

#include <maco/config.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeat_call.h>
#include <maco/parameter.h>

#define __MACO_map(f, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (f, 0, __VA_ARGS__)

#else

#include <maco/arguments.h>
#include <maco/detail/int_succ.h>
#include <maco/detail/int_prev.h>
#include <maco/loop.h>

#define __MACO_map_core_(next, f, g, m, n, x, ...)   __MACO_compose(f, g, m, x) __MACO_while(n)(next, (f, g, __MACO_inc(m), __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_2__(f, g, m, n, x, ...)           __MACO_map_core_(__MACO_map_1__, f, g, m, n, x, __VA_ARGS__)
#define __MACO_map_1__(f, g, m, n, x, ...)           __MACO_map_core_(__MACO_map_2__, f, g, m, n, x, __VA_ARGS__)
#define __MACO_map__(f, g, n, ...)                   __MACO_loop(n, __MACO_map_1__(f, g, 0, __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_(f, g, ...)                       __MACO_map__(f, g, __MACO_num_of_args(__VA_ARGS__), __VA_ARGS__)

#define __MACO_map(f, ...)                           __MACO_map_(f, __MACO_2nd,    __VA_ARGS__)
#define __MACO_map_i(f, ...)                         __MACO_map_(f, __MACO_keep__, __VA_ARGS__)

#endif

#endif //MACO_MAP_H
