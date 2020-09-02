//
// Created by Darwin Yuan on 2020/9/3.
//

#ifndef MACO_LOOP_DETAIL_H
#define MACO_LOOP_DETAIL_H

#define __MACO_eval_(...)   __MACO_eval_1(__MACO_eval_1(__MACO_eval_1(__VA_ARGS__)))
#define __MACO_eval_1(...)  __MACO_eval_2(__MACO_eval_2(__MACO_eval_2(__VA_ARGS__)))
#define __MACO_eval_2(...)  __MACO_eval_3(__MACO_eval_3(__MACO_eval_3(__VA_ARGS__)))
#define __MACO_eval_3(...)  __MACO_eval_4(__MACO_eval_4(__MACO_eval_4(__VA_ARGS__)))
//#define __MACO_eval_4(...)  __MACO_eval_5(__MACO_eval_5(__MACO_eval_5(__VA_ARGS__)))
//#define __MACO_eval_5(...)  __MACO_eval_6(__MACO_eval_6(__MACO_eval_6(__VA_ARGS__)))
//#define __MACO_eval_6(...)  __MACO_eval_7(__MACO_eval_7(__MACO_eval_7(__VA_ARGS__)))
#define __MACO_eval_4(...)  __VA_ARGS__

#endif //MACO_LOOP_H
