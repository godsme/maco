//
// Created by Darwin Yuan on 2020/9/3.
//

#ifndef MACO_LOOP_H
#define MACO_LOOP_H

#include <maco/condtion.h>
#include <maco/detail/loop.h>

#define __MACO_defer(macro) macro __MACO_empty()
#define __MACO_continue(macro, ...) __MACO_defer(macro) __VA_ARGS__
#define __MACO_when(n)      __MACO_if(n)(__MACO_continue, __MACO_eat__)
#define __MACO_eval(...)    __MACO_eval_(__VA_ARGS__)

#endif //MACO_LOOP_H
