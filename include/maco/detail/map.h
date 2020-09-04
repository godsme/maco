//
// Created by Darwin Yuan on 2020/9/4.
//

#ifndef MACO_DETAIL_MAP_H
#define MACO_DETAIL_MAP_H

#include <maco/arguments.h>
#include <maco/detail/int_succ.h>
#include <maco/detail/int_prev.h>
#include <maco/loop.h>

#define __MACO_map_core_1_(next, f, ud, g, m, n, x, ...)   __MACO_compose(f, g, m, x, ud) __MACO_while(n)(next, (f, ud, g, __MACO_inc(m), __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_1_2__(f, ud, g, m, n, x, ...)           __MACO_map_core_1_(__MACO_map_1_1__, f, ud, g, m, n, x, __VA_ARGS__)
#define __MACO_map_1_1__(f, ud, g, m, n, x, ...)           __MACO_map_core_1_(__MACO_map_1_2__, f, ud, g, m, n, x, __VA_ARGS__)
#define __MACO_map__(f, ud, g, n, ...)                     __MACO_loop(n, __MACO_map_1_1__(f, ud, g, 0, __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_(f, ud, g, ...)                         __MACO_map__(f, ud, g, __MACO_num_of_args(__VA_ARGS__), __VA_ARGS__)

#endif //MACO_DETAIL_MAP_H
