//
// Created by Darwin Yuan on 2020/9/3.
//

#ifndef MACO_LOOP_H
#define MACO_LOOP_H

#include <maco/condition.h>
#include <maco/detail/eval.h>
#include <maco/detail/eval_2.h>

#define __MACO_continue__(macro, ...) __MACO_defer(macro) __VA_ARGS__
#define __MACO_while(n)               __MACO_if(n)(__MACO_continue__, __MACO_eat__)
#define __MACO_when(n)                __MACO_while(n)

// this is the core for recursion
#define __MACO_loop(n, ...)         __MACO_concat(__MACO_eval_, n)(__VA_ARGS__)
#define __MACO_loop_2(n, ...)       __MACO_concat(__MACO_eval_2_, n)(__VA_ARGS__)

#endif //MACO_LOOP_H
