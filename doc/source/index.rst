========================
MACO
========================

.. note:: MACO 是一个图灵完备的 C/C++ macro 库

``C/C++`` 的宏一直被人诟病：难以理解，容易出错，名字悄然替换带来的麻烦，等等。

的确，只要 ``C++`` 有正式的语法手段可以解决你的问题，你就应该避免使用宏。``C++11`` 之后，越来越多的设施，
比如 ``constexpr`` ，模版变参支持，让宏的用武之地越来越小。

但是，在 ``C++ 23`` 支持编译时反射这种强大的元编程能力之前，宏依然有着不可替代的作用。但是，``C/C++`` 宏
对于需要它的程序员来讲，能力看起来又显得太弱。

是的，其能力的确不强。但同时，它又比大多数程序员所以为的，要强大很多。事实上，在一定程度上，它也可以做到图灵完备。
而图灵完备的能力，可以让程序员在不得不使用宏时，可以拥有更为强大的能力，解决更为棘手的问题。

``maco`` 库正是为此目的而创建。

我们来看看，通过 ``maco`` ，如何可以做到图灵完备的计算。

1. 条件判断：

.. code-block:: c++

   auto result = __MACO_if(__MACO_eq(3, 2))(
     10, // return 10 if 3 == 2
     20  // return 20 otherwise
   );

   ASSERT(result == 20);

2. 递归：

.. code-block:: c++

   #define __f(n) case n: return __MACO_succ(n);

   switch(number) {
     __MACO_simple_iterator_from_0(3, __f)
     default:  return 0;
   }

其被展开后，则变为：

.. code-block:: c++

   switch(number) {
     case 0: return 1;
     case 1: return 2;
     case 2: return 3;
     default:  return 0;
   }


而它的实现，背后则是使用了递归：

.. code-block:: c++

   #define __MACO_simple_iterator_0_core(next, n, f) __MACO_while(n)(next, (__MACO_prev(n), f)) f(n)
   #define __MACO_simple_iterator_2_(n, f) __MACO_simple_iterator_0_core(__MACO_simple_iterator_1_, n, f)
   #define __MACO_simple_iterator_1_(n, f) __MACO_simple_iterator_0_core(__MACO_simple_iterator_2_, n, f)
   #define __MACO_simple_iterator_from_0(n, f)  __MACO_loop(n, __MACO_simple_iterator_1_(__MACO_prev(n), f))

其中 ``__MACO_loop(n, ...)`` 和 ``__MACO_while(cond)`` 在这个迭代实现中，起到关键的作用。

而中间的 ``__MACO_simple_iterator_1_`` 和 ``__MACO_simple_iterator_2_`` 则是为了绕开 ``C/C++`` 禁止宏的自我引用
而不得不引入的重复定义。



- ``__MACO_num_of_args``

求一个宏展开参数的个数。比如：

.. code-block:: c++

   ASSERT(__MACO_num_of_args() == 0);
   ASSERT(__MACO_num_of_args(a) == 1);
   ASSERT(__MACO_num_of_args(a, b) == 2);
   ASSERT(__MACO_num_of_args(a, b, c, d, e) == 5);

这个宏对于处理变参问题极为有用。




