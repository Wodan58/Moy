 ![](Wynn.PNG)
==============

Introduction
============

This page presents a note about the technicalities of this Joy implementation.
The mechanisms of this implementation differ from the
[reference implementation](https://github.com/Wodan58/Joy).

Implementation details
======================

This implementation uses vectors instead of linked lists and it recurses
without overflowing the call stack.

The big advantage of stackless recursion is in the size of data structures that
can be handled. A program that builds a list of integers in idiomatic fashion
looks like this:

    echo '1 100000 from-to-list.' | build/joy.exe

This program fails in `joy0`, the original version. It also fails in `Joy` and
`joy1`. The reason is stack overflow. The original has a recursive garbage
collector that causes the stack overflow. `Joy` had Cheney's algorithm
implemented, that is not recursive but still fail because `from-to-list` makes
use of `linrec` and `linrec` recurses.

This implementation succeeds where other implementations fail. And that is just
an experiment. The normal Joy suffers from stack overflow and that can be
prevented by using an iterative algorithm, exactly what would be needed in most
other programming languages.
