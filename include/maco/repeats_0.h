//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_REPEATS_0_H
#define MACO_REPEATS_0_H

#include <maco/detail/repeats_0.h>

#define __MACO_repeat_from_0(n, macro, end_macro) __MACO_repeat_0_##n (macro) __MACO_end_macro_0_##n(end_macro)
#define __MACO_simple_repeat_from_0(n, macro) __MACO_repeat_from_0(n, macro, macro)

#endif //MACO_REPEATS_0_H
