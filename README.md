Moy
---

Build|Linux|Windows|Coverity
---|---|---|---
status|[![GitHub CI build status](https://github.com/Wodan58/Moy/actions/workflows/cmake.yml/badge.svg)](https://github.com/Wodan58/Moy/actions/workflows/cmake.yml)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14635.svg)](https://scan.coverity.com/projects/wodan58-moy)

This repository implements [Joy](https://github.com/Wodan58/Joy) and uses
[Lex & Yacc](https://sourceforge.net/projects/winflexbison/files/win_flex_bison-latest.zip) and the
[BDW garbage collector](https://github.com/ivmai/bdwgc). This
[document](https://github.com/Wodan58/Moy/blob/master/doc/MOYimplJOY.md)
explains the raison d'être.

Build instructions
------------------

    mkdir build
    cd build
    cmake ..
    cmake --build .

Build with MSVC
---------------

Install bdwgc in a bdwgc-subdirectory.

    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    copy Release\joy.exe

Running
-------

    joy -h

gives an overview of available options.

See also
--------

Implementation|Dependencies
--------------|------------
[42minjoy](https://github.com/Wodan58/42minjoy)|
[joy0](https://github.com/Wodan58/joy0)|
[Joy](https://github.com/Wodan58/Joy)|
[joy1](https://github.com/Wodan58/joy1)|[BDW garbage collector](https://github.com/ivmai/bdwgc)
[Foy](https://github.com/Wodan58/Foy)|[BDW garbage collector](https://github.com/ivmai/bdwgc)

Documentation|
-------------|
[Legacy Docs](https://wodan58.github.io)
[User Manual](https://wodan58.github.io/j09imp.html)
[Comparison (PDF)](https://github.com/Wodan58/HET/blob/master/doc/FIB.pdf)
[Maintenance Manual (PDF)](https://github.com/Wodan58/G3/blob/master/JOP.pdf)
