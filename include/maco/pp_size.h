//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_PP_SIZE_H
#define MACO_PP_SIZE_H

#include <maco/detail/pp_size.h>

#define __MACO_pp_size(...)           __MACO_pp_size_(__dummy__, ##__VA_ARGS__)
#define __MACO_overload(prefix, ...)  __MACO_paste(prefix, __MACO_pp_size(__VA_ARGS__))

#endif //MACO_PP_SIZE_H
