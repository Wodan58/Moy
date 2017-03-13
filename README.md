Moy
---

This is [Joy1](https://github.com/Wodan58/joy1) implemented with Lex and Yacc and some additions: round, fget, filetime, index, sametype, casting, and getch.
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Changes
-------

Echo of input to output is not supported.
Error messages are limited to "syntax error".

Installation
------------

In addition to the BDW garbage collector, it is wise to install CMake. Then run:

CMake -G "Unix Makefiles" or CMake -G "NMake Makefiles"

make or nmake
