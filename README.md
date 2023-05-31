Moy
---

Build|Linux|Windows|Coverity
---|---|---|---
status|[![GitHub CI build status](https://github.com/Wodan58/Moy/actions/workflows/cmake.yml/badge.svg)](https://github.com/Wodan58/Moy/actions/workflows/cmake.yml)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14635.svg)](https://scan.coverity.com/projects/wodan58-moy)

This project implements [joy1](https://github.com/Wodan58/joy1) with Lex and
Yacc; use of the [BDW garbage collector](https://github.com/ivmai/bdwgc) is
optional.

Build instructions
------------------

    cmake .
    cmake --build .

Changes
-------

Some builtins have been added: `casting`, `filetime`, `index`, `round`, and
`typeof`.
Directives borrowed from [42minjoy](https://github.com/Wodan58/42minjoy) are:
`%INCLUDE`, `%PUT`, and `%LISTING`.
The build system requires new builtins in only one location: as a .c file in
the src-directory.

Additions
---------

In addition to normal interpreter mode, this program offers two compile
options: -c and -l. Start the program with -h to see what they mean.
