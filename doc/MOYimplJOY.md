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

The source code contains a number of #ifdef, #ifndef, #if constructs that
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
`:`; the start of the code is situated immediately to the right of `:`.
As it happens, in this implementation, that is all there is. There are no dumps
and there are no values on the hardware stack.

_MSC_VER
--------

Special instructions on behalf of the Microsoft C compiler are guarded by these
defines.

REMEMBER_FILENAME
-----------------

In error reporting, the filename is not mentioned. The line where an error
occurred is shown, followed by a line that contains a `^`, followed by an
error message. That is presumably enough. But in case of many more files
in the future, it might become necessary to mention the filename where the
error occurred. That is when this define will be needed. This define can now
be used, because file and line are reported when this define is enabled.

SIGNAL_HANDLING
---------------

If `mygc` is used instead of the BDW garbage collector, this define offers the
possibility to catch a segment violation and print a user-selected error
message.
The use of this feature is not recommended, because it prevents during
debugging to pinpoint the exact location where the error occurred.
Also `mygc` is not recommended, as it is slower than the BDW garbage collector
and the extra dependency is overcome by building from source by the Microsoft
compiler or installing the BDW package in other environments.

JVERSION
--------

This define can be used to tell something about the compile options, such as
whether it is a Release build, and what the version number is.
The version happens to be always 1.0 and whether it is a Release build or not
can be seen by executing `ccmake .`. That program reads the latest
CMakeCache.txt and reports about the options available therein.

BDW_GARBAGE_COLLECTOR
---------------------

The BDW garbage collector creates an extra dependency, but if it can be
installed system wide, it is easy enough to link against it. It is faster than
`mygc`. The interface is kept the same, except that initialization is different.
The `mygc` needs to know what the top of the stack is, that is why it receives
the address of argc.

CORRECT_INTERN_LOOKUP
---------------------

This is a check that was originally not present in Joy. The check makes sure
that a name that is interned constitutes a valid identifier. If not, printing
the name may look very odd. In a colored version of Joy that could be remedied
by giving symbols their own color, but as it is, it may be better to prevent
illegal names.

SEARCH_EXEC_DIRECTORY
---------------------

This is an extension that allows sloppy locations of `usrlib.joy` and other
libraries. The aim is to make library files available without copying them to
a host of other directories. The original only looks in the current working
directory. That may prevent out-of-source builds in CMake.

USE_SNPRINTF
------------

Snprintf calculates the size of the buffer that is needed by printf. It makes
the use of printf safer. The downside is that snprintf is not available in the
ansi standard. Even so, it might be beneficial to use this define when snprintf
is available.

WIN32
-----

Static analyzers point to various flaws in the source code, such as the use of
`gmtime` and `localtime`, that should be replaced by _r functions. Ok, but
the new functions are not available on the Windows platform. That is why this
define is there. Maybe it should be replaced by a USE_R_FUNCTIONS define.
This define is no longer needed.

SOURCE_DATE_EPOCH
-----------------

This shell variable, when available during the compilation of main.c causes the
date and time stamp to be that of the last known version created by the author
of Joy. This timestamp indicates that the language is still the one from that
date, even though some builtins have been added since.

#if 0
-----

Some code is disabled with this define. It is code that is not executed and
still needs to be kept around in case of future changes.

YYDEBUG
-------

When activated, this define allows the user to see the parse tree,
as maintained by bison. A -y command flag is also required.

COSMO
-----

Compiling against the cosmopolitan library seems attractive, but the
combination of cosmopolitan and the BDW garbage collector may be difficult.

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

About the implementation: the aim is to not disturb the language. That means
that all tests in the test2 directory and all examples in the lib directory
should behave exactly as in the reference implementation of Joy.

What is different in this implementation is the use of vectors instead of
linked lists and the absence of recursion. There are exceptions: `get` and
`fget` use readfactor that may call readterm, that calls readfactor.

The big advantage of not using recursion is in the size of data structures that
can be handled. A program that builds a list of integers looks like this:

    echo '1 100000 from-to-list.' | ./joy.exe

This program fails in `joy0`, the original version. It also fails in `Joy`.
The reason is stack overflow. The original has a recursive garbage collector
that causes the stack overflow. `Joy` has Cheney's algorithm implemented, that
is not recursive but still fails because from-to-list makes use of `linrec` and
`linrec` recurses.

This implementation does not use recursion and so succeeds where other
implementations fail. There is also a downside: function calling is slower.

Summary
=======

Linked lists are not good engineering.
Recursion is not good engineering.
Dynamic memory is not good engineering.
Ok, this implementation uses dynamic memory. Lots of it.
