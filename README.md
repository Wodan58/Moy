Moy
---

Build|Linux|Windows
---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Moy.svg?branch=master)](https://travis-ci.org/Wodan58/Moy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)

This is [Joy1](https://github.com/Wodan58/joy1) implemented with Lex and Yacc and some additions: round, fget, filetime, nothing, index, sametype, casting, and getch.
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
