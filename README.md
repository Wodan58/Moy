Moy
---

Build|Linux|Windows|Coverity|Quality|Coverage|Codecov|Alerts
---|---|---|---|---|---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Moy.svg?branch=master)](https://travis-ci.org/Wodan58/Moy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14635.svg)](https://scan.coverity.com/projects/wodan58-moy)|[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Wodan58/Moy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Moy/context:cpp)|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Moy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Moy?branch=master)|[![Codecov](https://codecov.io/gh/Wodan58/Moy/branch/master/graph/badge.svg)](https://codecov.io/gh/Wodan58/Moy)|[![Alerts](https://img.shields.io/lgtm/alerts/g/Wodan58/Moy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Moy/alerts)

This project implements a version of [Joy1](https://github.com/Wodan58/joy1)
that is Minimally polymorph. Moy is implemented with Lex and Yacc and
in addition to datatype specific builtins, some other ones have been added:
casting, fget, filetime, getch, index, over, pick, round, and sametype.
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Changes
-------

Most builtins of Joy1 are supported in Moy. Conditions do not restore the
stack to what it was before the condition started, unless embedded in nullary,
unary, binary, or ternary. The stack is implemented as a tagless array of
values. The build system requires new builtins in only one location: as a .c
file in the src-directory. Runtime performance of compiled programs should be
good. The transition to a tagless stack is not yet complete.

Installation
------------

In addition to the BDW garbage collector, it is wise to install CMake. Then run:

CMake -G "Unix Makefiles" or CMake -G "NMake Makefiles"

make or nmake
