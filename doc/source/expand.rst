宏展开
==========================

一个 ``类函数宏`` 的展开，分为两个阶段：


阶段1：参数展开
-------------------------------

这个阶段，对宏的参数进行 **完全展开** 。``C99`` 对此阶段的定义如下：

.. C99: 6.10.3.1 Argument substitution
..
   After the arguments for the invocation of a function-like
   macro have been identified, argument substitution takes place.
   A parameter in the replacement list, unless preceded by a # or ## preprocessing
   token or followed by a ## preprocessing token (see below), is replaced by the
   corresponding argument after all macros contained therein have been expanded.
   Before being substituted, each argument’s preprocessing tokens are completely
   macro replaced as if they formed the rest of the preprocessing file; no other
   preprocessing tokens are available.

对于参数展开，其处理边界为其参数自身所包含（或展开后包含）的所有字符。做为参数分割的 ``逗号`` 、
或者宏的 ``右括号`` 之后的字符，都不会参与参数的 **完全展开** 过程。

注意，此时，每个参数的展开，都有各自独立的 **展开上下文** ，某个参数与宏同名，并不会被认为是 **自引用** 。

比如：

.. code-block:: c++

   #define foo(x) x + 10

``foo(foo(1))`` 将会首先被展开为 ``foo(1 + 10)`` ，进而被展开为 ``1 + 10 + 10`` 。其中，
``foo(1)`` 的展开有其独立的上下文，``foo(1 + 10)`` 则属于另一个展开上下文。

阶段2：参数替换后再次展开
-------------------------------

所有  **完全展开** 后的参数，在宏定义里进行替换之后，结合宏定义之后的其它字符，进行第二次 **完全展开** 。

``C99`` 对此定义如下：

.. C99: 6.10.3.4 Rescanning and further replacement
..
   After all parameters in the replacement list have been substituted and # and ## processing
   has taken place, all placemarker preprocessing tokens are removed. Then, the resulting
   preprocessing token sequence is rescanned, along with all subsequent preprocessing tokens
   of the source file, for more macro names to replace.

   If the name of the macro being replaced is found during this scan of the replacement list
   (not including the rest of the source file’s preprocessing tokens), it is not replaced. Furthermore,
   if any nested replacements encounter the name of the macro being replaced, it is not replaced. These
   nonreplaced macro name preprocessing tokens are no longer available for further replacement
   even if they are later (re)examined in contexts in which that macro name preprocessing token
   would otherwise have been replaced.

一个参数被完全展开之后，在其上下文里没有被标记为 ``自引用`` 的符号， 在宏的第二次扫描过程中，如果被发现可以和后面的符号（即圆括号）
形成一个 ``类函数宏`` "调用" ，则会按照 ``类函数宏`` 的方式进一步展开。比如：

.. code-block:: c++

   #define foo(x) x (1) + 20
   #define bar_10(y) y + 10
   #define concat(a, b) a ## b

``foo(concat(bar_, 10))`` 首先被展开为： ``bar_10(1)+20`` ，然后在第二次展开过程中，
进一步展开为 ``1+10+20`` 。

自引用
~~~~~~~~~~~~~~~

在第二阶段，正在被展开的宏的名字，会被标记为不可再展开，以避免 ``自引用`` 所导致的 ``无穷递归`` 问题；比如：

.. code-block:: c++

   #define foo(x) foo x


``foo((10))`` 被完全展开后的结果是 ``foo(10)`` ，而不是 ``foo 10`` 。因为第二次扫描时，因为 ``foo`` 和正在被展开的宏同名，
因而被标记为 ``不可展开`` 。从而 ``foo(10)`` 不再被当作一个 ``类函数宏`` 的"调用" 而进一步展开。

.. code-block:: c++

   #define bar(x, y) x + y
   #define foo(x, y) x(y, 10)

对于 ``foo(foo, bar)`` ，参数 ``foo`` 在外围的宏 ``foo`` 展开后的第二次扫描时，由于和正在展开的宏 ``foo`` 同名，因而
被标记为 ``不可展开`` 。因而最后的展开结果为 ``foo(bar, 10)`` ，而不是 ``10 + 10`` 。

.. code-block:: c++

   #define bar(x) foo x , bar((3,4))
   #define foo(x, y) bar((x+1, y+2))

``foo(10, 20)`` 被完全展开后的结果为 ``foo(10+1, 20+2),bar((3,4))`` ，因为在 ``foo(10, 20`` 的第二次
扫描过程中，进一步展开了 ``bar((10+1, 20+2))`` ，得到 ``foo(10+1, 20+2)`` ，但此时发现
``foo`` 和外层正在展开的宏 ``foo`` 同名，因而被标记为 ``不可展开`` 。同时，``bar((3,4))`` 也因为和正在
展开的 ``bar((10+1,20+2))`` 同名，因而，也被标记为 ``不可展开`` 。

由此可以看出，在一个宏的展开过程中，无论嵌套的有多深（比如上例中 ``foo(10, 20)`` 的展开中，嵌套
了 ``bar((10+1, 20+2))`` 的展开），只要和正在被展开的宏同名，都会被标记为 ``不可展开`` 。

并且一个符号被标记为 ``不可展开`` ，则此符号将在未来永远不可能再展开。哪怕其展开上下文已经发生了变化。

.. code-block:: c++

   #define foo(x) x, foo
   #define expand(...) __VA_ARGS__

``expand(foo(10)(20))`` 展开的结果是 ``10, foo(20)`` ，而不是 ``10, 20, foo`` 。因为在 ``foo(10)`` 的展开上下文里，
``foo`` 已经被标记为 ``不可展开`` ，此标记永远不会被清除。在离开其上下文后，回到 ``expand(10, foo(20)`` 的展开上下文，
``foo`` 会依然保持 ``不可展开`` ，即便看起来 ``foo(20)`` 是一个可以继续展开的 ``类函数宏`` 。


递归
-----------------

正是因为 ``C/C++`` 宏在设计时，刻意避免自引用问题，因而，你无法直接通过 ``自引用`` 实现递归（递归都是自引用的）。

而为了实现递归，必须做到：

1. 在一个宏，假设其名字为 ``foo_1`` ，的展开过程中，不要出现自引用。即，你必须用另外一个名字，比如：``foo_2`` ；
   ``foo_2`` 展开后，可引用回 ``foo_1`` ，从而通过这种互相引用的技术实现递归； 比如：

.. code-block::

   #define foo_1(n) n+1, foo_2(n+1)
   #define foo_2(n) n+1, foo_1(n+1)


2. 但你必须保证 ``foo_2`` 在 ``foo_1`` 的展开过程中，不会展开；同样，你也必须保证 ``foo_2`` 在展开的过程中，不会展开 ``foo_1`` 。
   否则，预处理器依然会发现这个自引用；从而将其标记为 ``不可展开`` 。

避免这种展开的技术是放入一个另外一个宏，比如：

.. code-block:: c++

   #define empty()
   #define foo_1(n) n+1, foo_2 empty() (n+1)
   #define foo_2(n) n+1, foo_1 empty() (n+1)

这样，在 ``foo_1(0)`` 展开过程中的第二次扫描时，发现 ``foo_2`` 后面并没有直接有 ``(`` 符号，因而，将其看作一个普通
符号，而不是一个 ``类函数宏`` ，因而不会将其展开。即，第二次扫描结束后，其结果为： ``0+1, foo_2 (0+1)`` 。

如果想让 ``foo_2(0+1)`` 进一步展开，则必须进行一次新的扫描；此时，就必须明确告诉预处理器：

.. code-block:: c++

   #define eval(...) __VA_ARGS__

   eval(foo_1(0)) // expand to: 0+1, 0+1+1, foo_1(0+1+1)

注意，在进行 ``eval(0+1, foo_2 (0+1))`` 展开时，已经离开了 ``foo_1(0)`` 的展开上下文，因而，再次出现 ``foo_1`` 将不会
被认为是自引用。

对于上面的结果，如果我们再次用 ``eval`` 进行展开：

.. code-block:: c++

   eval(eval(foo_1(0))
   // 0+1, 0+1+1, 0+1+1+1, foo_2(0+1+1+1)


再 ``eval`` 一次，则得到：

.. code-block:: c++

   eval(eval(eval(foo_1(0))))
   // 0+1, 0+1+1, 0+1+1+1, 0+1+1+1+1, foo_1(0+1+1+1+1)

从中，你可以清晰的看出，这是一个递归过程。

现在剩下两个问题：

1. 如何控制 ``eval`` 次数？
2. 如何去掉最后一个多余的递归？（最后一个例子中的 ``foo_1(0+1+1+1+1)`` )

控制 ``eval`` 次数
--------------------------

至少有两种方法可以控制 ``eval`` 次数。

第一种方法是，不管具体的次数，而是提供足够多的次数。具体定义如下：

.. code-block:: c++

   #define __MACO_eval_4(...)  __VA_ARGS__
   #define __MACO_eval_3(...)  __MACO_eval_4(__MACO_eval_4(__MACO_eval_4(__VA_ARGS__)))
   #define __MACO_eval_2(...)  __MACO_eval_3(__MACO_eval_3(__MACO_eval_3(__VA_ARGS__)))
   #define __MACO_eval_1(...)  __MACO_eval_2(__MACO_eval_2(__MACO_eval_2(__VA_ARGS__)))
   #define __MACO_eval(...)    __MACO_eval_1(__MACO_eval_1(__MACO_eval_1(__VA_ARGS__)))

对于这样的定义，每一层展开 ``3n + 1`` 次。具体对于上面的定义，则为 ``(3 * (3 * (3 * (3 + 1) + 1) + 1) + 1)`` 次。

你可以调整每一层的嵌套次数和层数，决定最终的展开次数。

这种方法的优点是：代码很少。而其缺点则是，无论你实际需要展开多少次，它总是展开最大次数。

而第二种方法：定义足够多的展开次数，然后根据需要精确决定展开次数。具体定义如下：

.. code-block:: c++

   #define __MACO_eval_0(...)
   #define __MACO_eval_1(...) __VA_ARGS__
   #define __MACO_eval_2(...)   __MACO_eval_1(__VA_ARGS__)
   #define __MACO_eval_3(...)   __MACO_eval_2(__VA_ARGS__)
   #define __MACO_eval_4(...)   __MACO_eval_3(__VA_ARGS__)
   #define __MACO_eval_5(...)   __MACO_eval_4(__VA_ARGS__)
   #define __MACO_eval_6(...)   __MACO_eval_5(__VA_ARGS__)
   #define __MACO_eval_7(...)   __MACO_eval_6(__VA_ARGS__)
   #define __MACO_eval_8(...)   __MACO_eval_7(__VA_ARGS__)
   #define __MACO_eval_9(...)   __MACO_eval_8(__VA_ARGS__)
   #define __MACO_eval_10(...)   __MACO_eval_9(__VA_ARGS__)
   // more ...

   #define __MACO_eval(n, ...) __MACO_eval_## n(__VA_ARGS__)

这种方法的缺点是：需要枚举每一个定义（可以通过脚本语言自动生成）；但优点是：让 ``IDE`` / 预处理器 不做无用的工作。

终止递归
--------------------------

像任何程序一样，我们需要一个终止递归的条件。绝大多数场景下，我们都可以通过递归次数来控制递归的结束。对于上面的例子，
我们可以用如下代码解决：

.. code-block:: c++

   #define __MACO_eat(...)
   #define __MACO_continue(f, ...) __MACO_defer(f) __VA_ARGS__
   #define __MACO_while(n)         __MACO_if(n)(__MACO_continue, __MACO_eat)

   #define foo_1(n) __MACO_while(__MACO_dec(n))(foo_2, (__MACO_dec(n))) , n
   #define foo_2(n) __MACO_while(__MACO_dec(n))(foo_1, (__MACO_dec(n))) , n

其中，``__MACO_while(n)`` 的语意为 ``while(n > 0)`` 。 如果条件成立，则用 ``__MACO_continue`` 进行扩展，
``__MACO_continue(foo_1, (__MACO_dec(n)))`` 的展开结果为 ``foo_1 (n-1)`` ，继续递归；如果条件不成立，则
使用 ``__MACO_eat`` 进行展开，结果为空；从而结束了递归。

将之前所谈的结合在一起，则 ``foo`` 的最终定义为：

.. code-block:: c++

   #define foo(n) __MACO_eval(n, foo_1(__MACO_dec(n)))


