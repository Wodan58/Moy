Moy
---

Build|Linux|Windows|Coverity
---|---|---|---
status|[![GitHub CI build status](https://github.com/Wodan58/Moy/actions/workflows/cmake.yml/badge.svg)](https://github.com/Wodan58/Moy/actions/workflows/cmake.yml)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14635.svg)](https://scan.coverity.com/projects/wodan58-moy)

This project implements [Joy](https://github.com/Wodan58/Joy) and uses the
[BDW garbage collector](https://github.com/ivmai/bdwgc). The document in the
doc directory explains the raison d'être of this implementation.

Build instructions
------------------

    cd build
    cmake ..
    cmake --build .

There is a customized version of usrlib.joy waiting in the build directory.

Changes
-------

Some builtins have been added compared to Joy: `casting`, `filetime`, `over`,
`pick`, `round`, and `typeof`.
Directives borrowed from [42minjoy](https://github.com/Wodan58/42minjoy) are:
`%INCLUDE`, `%PUT`, and `%LISTING`.
The build system requires new builtins in only one location: as a .c file in
the src-directory.

Use cases
---------

[projecteuler.net](https://projecteuler.net), that's why the BIGNUM arithmetic
was needed. This is commented out, because it is still in development.
The stackless approach makes idiomatic Joy possible on big datasets.
