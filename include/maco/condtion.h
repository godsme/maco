//
// Created by Darwin Yuan on 2020/9/2.
//

#ifndef MACO_CONDTION_H
#define MACO_CONDTION_H

#include <maco/basic.h>

////////////////////////////////////////////////////////////////////////
#define __MACO_check_0__(...)  __MACO_2nd(__VA_ARGS__, 0)

// __MACO_not_n does NOT exist, 0 is the 2nd parameter of __MACO_2nd.
// __MACO_not_0 exists,         1 is the 2nd parameter of __MACO_2nd.
#define __MACO_not(n) __MACO_check_0__(__MACO_concat(__MACO_not_, n))
#define __MACO_not_0  __MACO_placeholder, 1

////////////////////////////////////////////////////////////////////////
#define __MACO_check_1__(...)  __MACO_2nd(__VA_ARGS__, 1)

// __MACO_bool_n does NOT exist, 1 is the 2nd parameter of __MACO_2nd.
// __MACO_bool_0 exists,         0 is the 2nd parameter of __MACO_2nd.
#define __MACO_bool(n) __MACO_check_1__(__MACO_concat(__MACO_bool_, n))
#define __MACO_bool_0  __MACO_placeholder, 0

////////////////////////////////////////////////////////////////////////
#define __MACO_if(n) __MACO_paste(__MACO_if_, __MACO_bool(n))
#define __MACO_if_0(true_branch, false_branch) false_branch
#define __MACO_if_1(true_branch, false_branch) true_branch

#endif //MACO_CONDTION_H
