 ![](Wynn.PNG)
==============

Introduction
============

This presents a note about the technicalities of this Joy implementation.
The mechanisms of this implementation differ from the
[reference implementation](https://github.com/Wodan58/Joy).
The language itself should be the same. Whatever is not the same should be
repaired, unless it is a consequence of using Flex and Bison.

Compile options
===============

The source code contains a number of `#ifdef`, `#ifndef`, `#if` constructs that
modify what becomes part of the final binary. Explaining these defines may
illustrate why this implementation exists.

NCHECK
------

This, when defined, turns off all runtime checks. It is not recommended to
compile the source without runtime checks. There are some checks that are open
to discussion, such as that in `plus` and `minus`. It is allowed to add an
integer to a character. It is not allowed to add a character to an integer,
even though it could be useful, for example in the following program:

    5 "test" [+] map.

The 5 needs to be pushed only once, but this construct is rejected by the
type checker.

STATS
-----

This define can be used to report about the number of seconds it took to
execute a program and to report about the number of calls to exeterm and the
number of operations executed. That last number might be interesting when
comparing different algorithms. It can detect what algorithm takes fewer steps.

TRACING
-------

Tracing allows inspection of program execution. It shows stack and code
separated by `:`. The top of the stack is presented immediately to the left of
`:`; the start of the code is situated immediately to the right of `:`. As it
happens, in this implementation, that is all there is. There are no dumps and
there are no values on the hardware stack.

_MSC_VER
--------

Special instructions on behalf of the Microsoft C compiler are guarded by these
defines.

JVERSION
--------

This define can be used to tell something about the compile options, such as
whether it is a Release build, and what the version number is. The version
happens to be always 1.0 and whether it is a Release build or not can be seen
by executing `ccmake .`. That program reads the latest CMakeCache.txt and
reports about the options available therein.

SOURCE_DATE_EPOCH
-----------------

This shell variable, when available during the compilation of `main.c` causes
the date and time stamp to be that of the last known version created by the
author of Joy. This timestamp indicates that the language is still the one from
that date, even though some builtins have been added since.

#if 0
-----

Some code is disabled with this define. It is code that is not executed and
still needs to be kept around in case of future changes.

YYDEBUG
-------

When activated, this define allows the user to see the parse tree, as
maintained by bison. A `-y` command flag is also required.

ALARM
-----

It is possible to set a time limit, such as -DALARM=99, in order to satisfy
restrictions imposed on solutions submitted to projecteuler.net. That website
presents mathematical challenges that can be solved by programming a computer
and restricts solutions to one minute. A minute has 100 seconds, right?

ARITY
-----

This define allows debugging arity calculations. It is important that save and
restore of the stack is prevented by copying data that will be destroyed by a
condition. This define helps to locate code that is not helpful in that
respect.

COPYRIGHT
---------

There is a copyright notice. The code that enables this can be turned off with
this define. Or rather, it can be turned on.

OVERWRITE
---------

Errors and warnings should normally be reported, as that is part of the
functionality that can be expected from a language processor. With this define
enabled, the possibility exists to suppress warning messages.

SYMBOLS
-------

The functionality that allows printing the symbol table needs this define on,
before it can be used. These last three defines have been added in order to
reduce the functionality in the main function to the bare minimum. The only
remaining option, -h, cannot be disabled.

Implementation details
======================

About the implementation: the aim is to leave the language untouched. That
means that all tests in the test2 directory and all examples in the lib
directory should behave exactly as in the reference implementation of Joy.

What is different in this implementation is the use of vectors instead of
linked lists and the stackless recursion. There are exceptions: `get` and
`fget` use readfactor that may call readterm, that calls readfactor.

The big advantage of stackless recursion is in the size of data structures that
can be handled. A program that builds a list of integers looks like this:

    echo '1 100000 from-to-list.' | build/joy.exe

This program fails in `joy0`, the original version. It also fails in `Joy` and
`joy1`. The reason is stack overflow. The original has a recursive garbage
collector that causes the stack overflow. `Joy` has Cheney's algorithm
implemented, that is not recursive but still fails because `from-to-list` makes
use of `linrec` and `linrec` recurses.

This implementation is stackless and so succeeds where other implementations
fail. There is also a downside: function calling is slower.

Benchmark
---------

Implementation|fib(40)|lst(10000)|sieve(3000)
--------------|-------|----------|-----------
      42minjoy|    1m8|          |
          joy0|     44|      0.06|        0.4
           Joy|   1m12|      0.07|        1.0
          joy1|   3m57|      0.07|        2.1
           Moy|     2m|      0.08|        1.5

Moy is after all not the slowest implementation.
