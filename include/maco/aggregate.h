//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_AGGREGATE_H
#define MACO_AGGREGATE_H

#include <maco/basic.h>
#include <maco/pp_size.h>

#define __MACO_var_full(x) __MACO_swap_ x
#define __MACO_var_name(x) __MACO_1st   x
#define __MACO_var_type(x) __MACO_rest  x

#define __MACO_foreach(macro, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (macro, 0, __VA_ARGS__)

#endif //MACO_AGGREGATE_H
