//
// Created by Darwin Yuan on 2020/9/4.
//

#ifndef MACO_COMPARE_H
#define MACO_COMPARE_H

#include <maco/natural.h>

#define __MACO_eq(m, n)                __MACO_not(__MACO_sub(m, n))
#define __MACO_ne(m, n)                __MACO_bool(__MACO_sub(m, n))
#define __MACO_gt(m, n)                __MACO_gt_0(__MACO_sub(m, n))
#define __MACO_lt(m, n)                __MACO_gt_0(__MACO_sub(n, m))
#define __MACO_gte(m, n)               __MACO_gte_0(__MACO_sub(m, n))
#define __MACO_lte(m, n)               __MACO_gte_0(__MACO_sub(n, m))

#endif //MACO_COMPARE_H
