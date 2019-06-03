Moy
---

Build|Linux|Windows|Coverity|Coverage|Codecov|Quality|Alerts
---|---|---|---|---|---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Moy.svg?branch=master)](https://travis-ci.org/Wodan58/Moy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14635.svg)](https://scan.coverity.com/projects/wodan58-moy)|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Moy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Moy?branch=master)|[![Codecov](https://codecov.io/gh/Wodan58/Moy/branch/master/graph/badge.svg)](https://codecov.io/gh/Wodan58/Moy)|[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Wodan58/Moy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Moy/context:cpp)|[![Alerts](https://img.shields.io/lgtm/alerts/g/Wodan58/Moy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Moy/alerts)

This project implements a version of [Joy](https://github.com/Wodan58/joy1).
Conditions do not restore the stack to what it was before the condition started,
unless embedded in nullary, unary, binary, or ternary.
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Changes
-------

Most builtins of Joy are supported in Moy.
Some other ones have been added: casting, fget, filetime, getch, index, over, pick,
round, and sametype.
The build system requires new builtins in only one location: as a .c file in the
src-directory.

Installation
------------

In addition to the BDW garbage collector, it is wise to install CMake. Then run:

    ln -s ../bdwgc
    cmake .
    cmake --build .

And run:

    cd lib
    make -f regres.mak

There is a *test* directory with an experimental tagless array version of the stack.
