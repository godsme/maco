//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_BASIC_H
#define MACO_BASIC_H

#define __MACO_empty()
#define __MACO_defer(f) f __MACO_empty()

#define __MACO_concat(x, y) x ## y
#define __MACO_paste(x, y) __MACO_concat(x, y)

#define __MACO_stringify_(x) #x
#define __MACO_stringify(x) __MACO_stringify_(x)

#define __MACO_keep__(...)  __VA_ARGS__
#define __MACO_eat__(...)

#define __MACO_split__(...) __VA_ARGS__ ,

#define __MACO_1st__(a, ...)       a
#define __MACO_1st(...)            __MACO_1st__(__VA_ARGS__)

#define __MACO_2nd__(a, b, ...)    b
#define __MACO_2nd(...)            __MACO_2nd__(__VA_ARGS__)

#define __MACO_take_2__(a, b, ...) a, b
#define __MACO_take_2(...)         __MACO_take_2__(__VA_ARGS__)

#define __MACO_rest__(a, ...) __VA_ARGS__
#define __MACO_rest(...) __MACO_rest__(__VA_ARGS__)

#define __MACO_merge_2__(x, y)  x y
#define __MACO_merge_2(x, y)    __MACO_merge_2__(x,y)

#define __MACO_swap__(x, y)     y, x
#define __MACO_swap(x, y)       __MACO_swap__(x, y)

#define __MACO_merge_swap(x, y)   y x

#define __MACO_defer_invoke(f, ...)   __MACO_defer(f) (__VA_ARGS__)

#define __MACO_invoke(f, ...)         f(__VA_ARGS__)
#define __MACO_compose(f, g, ...)     __MACO_invoke(f, g(__VA_ARGS__))

#define __MACO_invoke_2(f, ...)       f(__VA_ARGS__)
#define __MACO_compose_2(f, g, ...)   __MACO_invoke_2(f, g(__VA_ARGS__))

#define __MACO_template_type(...) std::decay_t<decltype(std::declval<__VA_ARGS__>())>

#endif //MACO_BASIC_H
