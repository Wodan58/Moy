 ![](Wynn.PNG)
======================

Introduction
============

This is commentary about the programming language JOY.

Function
========

The question is whether or not Joy is a purely functional programming
language. The author, Manfred von Thun, seems to think it is, even in
the presence of I/O, that is generally considered a side-effect and not
functional.

The first question then is: what is a function? *Definition*: a function
gives the same output whenever the input is the same. This definition
does not specify where output and input is located.

    Example: c = f(a, b);

Function f has parameters a and b and output c. The question is whether
parameters are all the input and whether c is all the output. Is it
possible that global variables, the file system can also be affected by f?
According to the definition, this is possible. That makes it more
difficult for the reader of the program. He/she has to lookup the
definition of f to see if any global variables and/or files are affected.
Using this definition, Joy is certainly functional, and so is assembly.

    Another example: c = rand();

The rand-function is known to give a different return value whenever it
is called. Is rand() a function? It takes no parameters, so it looks as
if the same input gives different results. The answer is that rand()
makes use of seed as input and when given the same seed every time it is
called, rand() produces the same output:

    srand(1);
    c = rand();
    srand(1);
    d = rand();

c and d in the example are equal. That makes rand() a function. In
addition to the return value, rand also modifies the seed. Thus, rand
has the seed as input and also as output in addition to the return value.

    Yet another example: c = time();

The time-function reports a different time whenever it is called. Same
with `clock`. Are these functions? Not according to the definition, no.
Because no memory location is updated because of `time`, it becomes
unexplained why `time` reports differently each time it is called. But that
does not make Joy non-functional. In Joy words are functions from stack
to stack and `time` behaves as expected: it returns a new stack with a new
value on top, compared to the old stack. Where that value comes from is
not important. It is still a function from stack to stack.

The same reasoning as done for `time` can be done for I/O functions. They
take a stack, possibly with a file-pointer on top and return a new stack
with a value read from the file that is pointed to by the file-pointer.
These I/O functions are still functions from stack to stack in Joy.

There is another aspect about functional programming languages and that
is that there is no state. File-pointers point to a structure that
maintains state, such as the seek position. Also, the file that file
pointers point to can be open or closed. That too, is state.

And there is another aspect about Joy and that is that Joy has no
assignment. So, Joy has `getenv` from the C standard library, but no
`setenv`. The latter would introduce assignable variables and that is
not allowed.

All of this functionality has to do with two problems that need to be
addressed, when programming. The first is that bugs need to be
reproducable and that is only possible, if the program behaves the same
when given the same input. It requires careful considerations what
exactly is the input of a program. The second problem is that it must
be possible to split a large program in smaller pieces, where each
piece can be studied in isolation. For example, when evaluating
`2 3 +` the result will always be `5` whether the evaluation is done
at compile-time or whether it is done at runtime. The only caveat in
Joy is that quoted terms are not always evaluated, so it is not
possible to change `[2 3 +]` into `[5]` because a list of 1 item is
not the same as a list of 3 items.

Program
=======

So what is a program in Joy? *Definition*: a program is a term followed
by a full stop. And a term is zero or more factors. Ok, then what about
this:

    DEFINE year == 1999.
    year.
    DEFINE year == 2000.
    year.

First 1999 is printed and then 2000. How can the same program give
different output? The answer is that *year* is not the full program
source code. The definitions that precede the program are part of the
source code of the program. In fact, the substitution that is defined
can be done at compile time. When doing that, this is the result:

    1999.
    2000.

Now it is obvious that the two programs give different output.

I/O
===

    get get +.
    123 456

Joy differs from Forth in that first an entire program is read and
compiled and only then executed. The effect of that can be seen here.
If *get* were to execute as soon as it has been read, it would read the
second get and + would complain that two parameters are expected on the
stack and there is only one. Another question is how a compiler deals
with this source code. The compiler is not going to read its own source
code, like the interpreter does, so if the same input source is used as
displayed here, there will be two integers on the stack that the
interpreter adds up and the compiled program remembers. At runtime,
*get* reads from stdin as normal. But there is a choice here. The
compiler chooses to defer I/O statements till runtime, because that is
usually the reason why a program is run. The compiler could also execute
these words at compile time and then the addition can also be done at
compile time, leaving only the output of the sum till runtime.

Rewriting
=========

Joy can be implemented with a rewriting engine. Here it is explained
how that can be done.

There is only one object, the program, and it is implemented as a doubly
linked list. The stack pointer, stk, serves double purpose as stack
pointer and as instruction pointer. Stk points to the stack, as usual,
and stk-&gt;prev points to the next instruction. Because there is only
one object, whenever a subroutine must be carried out, its body must
replace the call to the subroutine in the doubly linked list. And that
means copying the body of that subroutine into the program. An example
shows the execution trace of a program:

    ; . 1 popd dupd
    ; 1 . popd dupd
    ; 1 popd ; . dupd
    ; 1 popd ; dupd ; .

This example causes a runtime error when executed in Joy. The rewriting
proceeds as if nothing happened. The dot is the stk pointer and the
semicolon is a special node, with the next-pointer pointing to itself,
thus marking the end of the stack. Instead of generating a runtime
error, the rewriting engine simply pushes an end of stack node. What
rests is a program that, when executed by Joy, exhibits the same
behavior as when Joy was used in the first place.

As explained, the rewriting engine will be slower when interpreted,
compared to Joy. This engine profits the compiler. The compiler uses it
to evaluate as much as possible before writing the resulting program to
disk. The compiler can also use the stack, like the interpreter. The
results are the same, except that a separate stack is faster and the
compiled program will have to use that separate stack anyway, because
the program then will be x86 or some other bytecode.
