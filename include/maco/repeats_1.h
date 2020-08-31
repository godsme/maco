//
// Created by Darwin Yuan on 2020/8/31.
//

#ifndef MACO_REPEATS_1_H
#define MACO_REPEATS_1_H

#include <maco/detail/repeats_1.h>

#define __MACO_repeat_from_1(n, macro, end_macro) __MACO_repeat_1_##n (macro) __MACO_end_macro_1_##n(end_macro)
#define __MACO_simple_repeat_from_1(n, macro) __MACO_repeat_from_1(n, macro, macro)

#endif //MACO_REPEATS_1_H
