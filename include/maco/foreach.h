//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_FOREACH_H
#define MACO_FOREACH_H

#include <maco/pp_size.h>
#include <maco/repeat_call.h>

#define __MACO_foreach(macro, ...) \
__MACO_overload(__MACO_repeat_call_, __VA_ARGS__) (macro, 0, __VA_ARGS__)

#endif //MACO_FOREACH_H
