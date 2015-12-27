Moy
---

This is [Joy1](https://github.com/Wodan58/joy1) implemented with Lex and Yacc and some additions.
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Changes
-------

Echo of input to output is not supported, because Lex does not register input lines.
Error messages are limited to "syntax error", because of Yacc's limited support for error handling.

Installation
------------

In addition to the BDW garbage collector, it is wise to install CMake. Then run:

CMake -G "Unix Makefiles"

make
