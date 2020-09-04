//
// Created by Darwin Yuan on 2020/9/4.
//

#ifndef MACO_INDEX_SEQ_H
#define MACO_INDEX_SEQ_H

#include <maco/loop.h>
#include <maco/arguments.h>
#include <maco/detail/int_prev.h>

#define __MACO_index_seq_core(next, n) __MACO_while(n)(next, (__MACO_prev(n))) n,
#define __MACO_index_seq_2_(n) __MACO_index_seq_core(__MACO_index_seq_1_, n)
#define __MACO_index_seq_1_(n) __MACO_index_seq_core(__MACO_index_seq_2_, n)
#define __MACO_index_seq__(n) __MACO_loop(n, __MACO_index_seq_1_(__MACO_prev(n)))
#define __MACO_make_index_seq__(n)  __MACO_index_seq__(n) n
#define __MACO_make_index_seq(n)  __MACO_if(n)(__MACO_make_index_seq__(__MACO_prev(n)),)

#endif //MACO_INDEX_SEQ_H
