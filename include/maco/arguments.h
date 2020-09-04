//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_ARGUMENTS_H
#define MACO_ARGUMENTS_H

#include <maco/detail/pp_size.h>

#define __MACO_num_of_args(...)          __MACO_pp_size_(__dummy__, ##__VA_ARGS__)
#define __MACO_overload(prefix, ...)     __MACO_paste(prefix, __MACO_num_of_args(__VA_ARGS__))

#endif //MACO_ARGUMENTS_H
