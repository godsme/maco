//
// Created by Darwin Yuan on 2020/9/4.
//

#ifndef MACO_DETAIL_MAP_2_H
#define MACO_DETAIL_MAP_2_H

#include <maco/arguments.h>
#include <maco/detail/int_succ.h>
#include <maco/detail/int_prev.h>
#include <maco/loop.h>

#define __MACO_map_core_2_(next, f, ud, g, m, n, x, ...)   __MACO_compose_2(f, g, m, x, ud) __MACO_while(n)(next, (f, ud, g, __MACO_inc(m), __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_2_2__(f, ud, g, m, n, x, ...)           __MACO_map_core_2_(__MACO_map_2_1__, f, ud, g, m, n, x, __VA_ARGS__)
#define __MACO_map_2_1__(f, ud, g, m, n, x, ...)           __MACO_map_core_2_(__MACO_map_2_2__, f, ud, g, m, n, x, __VA_ARGS__)
#define __MACO_map_2__(f, ud, g, n, ...)                   __MACO_loop_2(n, __MACO_map_2_1__(f, ud, g, 0, __MACO_dec(n), __VA_ARGS__))
#define __MACO_map_2_(f, ud, g, ...)                       __MACO_map_2__(f, ud, g, __MACO_num_of_args(__VA_ARGS__), __VA_ARGS__)

#endif //MACO_DETAIL_MAP_H
