//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_MAP_H
#define MACO_MAP_H

#include <maco/config.h>

#if USING_FAST_EXPANSION
#include <maco/detail/repeat_call.h>
#include <maco/arguments.h>
#include <maco/basic.h>

#define __MACO_map(f, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (f, __MACO_2nd, __MACO_empty(), 0, __VA_ARGS__)

#define __MACO_map_i(f, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (f, __MACO_2, __MACO_empty(), 0, __VA_ARGS__)

#define __MACO_map_x(f, x, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (f, __MACO_rest, x, 0, __VA_ARGS__)

#define __MACO_map_x_i(f, x, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (f, __MACO_keep__, x, 0, __VA_ARGS__)

#else

#include <maco/detail/map.h>

#define __MACO_map(f, ...)              __MACO_map_(f, __MACO_empty(), __MACO_2nd,    __VA_ARGS__)
#define __MACO_map_i(f, ...)            __MACO_map_(f, __MACO_empty(), __MACO_2, __VA_ARGS__)
#define __MACO_map_x(f, x, ...)         __MACO_map_(f, x, __MACO_rest, __VA_ARGS__)
#define __MACO_map_x_i(f, x, ...)       __MACO_map_(f, x, __MACO_keep__, __VA_ARGS__)

#endif

#endif //MACO_MAP_H
