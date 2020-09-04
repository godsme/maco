//
// Created by Darwin Yuan on 2020/9/4.
//

#ifndef MACO_INDEX_SEQ_H
#define MACO_INDEX_SEQ_H

#include <maco/basic.h>
#include <maco/iterator_0.h>

#define __MACO_index__(n) n ,
#define __MACO_make_index_seq(n)  __MACO_repeat_from_0(n, __MACO_index__, __MACO_keep__)

#define __MACO_token__(prefix, n) __MACO_paste(prefix, n) ,
#define __MACO_make_token_seq(prefix, n)  __MACO_repeat_ud_from_0(n, prefix, __MACO_token__, __MACO_paste)

#endif //MACO_INDEX_SEQ_H
