//
// Created by Darwin Yuan on 2020/8/30.
//

#ifndef MACO_BASIC_H
#define MACO_BASIC_H

#define __MACO_empty()
#define __MACO_concat(x, y) x ## y
#define __MACO_paste(x, y) __MACO_concat(x, y)

#define __MACO_stringify_(x) #x
#define __MACO_stringify(x) __MACO_stringify_(x)

#define __MACO_keep__(...) __VA_ARGS__
#define __MACO_eat__(...)
#define __MACO_split__(...) __VA_ARGS__ ,

#define __MACO_1st__(a, ...) a
#define __MACO_1st(...) __MACO_1st__(__VA_ARGS__)

#define __MACO_rest__(a, ...) __VA_ARGS__
#define __MACO_rest(...) __MACO_rest__(__VA_ARGS__)

#define __MACO_merge_2_(x, y) x y
#define __MACO_swap_(x, y)    y x

#define __MACO_template_type(...) std::decay_t<decltype(std::declval<__VA_ARGS__>())>

#endif //MACO_BASIC_H
