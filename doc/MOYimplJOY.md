 ![](Wynn.PNG)
==============

Introduction
============

This page presents a note about the technicalities of this Joy implementation.
The mechanisms of this implementation differ from the
[reference implementation](https://github.com/Wodan58/Joy).
The language itself should be the same. Whatever is not the same should be
repaired, unless it is a consequence of using Flex and Bison.

Implementation details
======================

About the implementation: the aim is to leave the language untouched. That
means that all tests in the test2 directory and all examples in the lib
directory should behave exactly as in the reference implementation of Joy.

What is different in this implementation is the use of vectors instead of
linked lists and the stackless recursion. There are exceptions: `get` and
`fget` use `readfactor` that may call `readterm`, that calls `readfactor`.

The big advantage of stackless recursion is in the size of data structures that
can be handled. A program that builds a list of integers in idiomatic fashion
looks like this:

    echo '1 100000 from-to-list.' | build/joy.exe

This program fails in `joy0`, the original version. It also fails in `Joy` and
`joy1`. The reason is stack overflow. The original has a recursive garbage
collector that causes the stack overflow. `Joy` has Cheney's algorithm
implemented, that is not recursive but still fails because `from-to-list` makes
use of `linrec` and `linrec` recurses.

This implementation is stackless and so succeeds where other implementations
fail. There is a downside: function calling is slower.
