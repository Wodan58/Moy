Moy
---

Build|Linux|Windows|Coverage
---|---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Moy.svg?branch=master)](https://travis-ci.org/Wodan58/Moy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Moy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Moy?branch=master)

This is [Joy1](https://github.com/Wodan58/joy1) implemented with Lex and Yacc and some additions: round, fget, filetime, nothing, index, sametype, casting, getch, over and pick.
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Changes
-------

Some builtins are not supported. Some other ones have been added.

Installation
------------

In addition to the BDW garbage collector, it is wise to install CMake. Then run:

CMake -G "Unix Makefiles" or CMake -G "NMake Makefiles"

make or nmake
