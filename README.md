Moy
---

Build|Linux|Windows|Coverity|Coverage|Codecov|Quality|Alerts
---|---|---|---|---|---|---|---
status|[![Travis CI build status](https://travis-ci.com/Wodan58/Moy.svg?branch=master)](https://travis-ci.com/Wodan58/Moy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Moy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Moy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14635.svg)](https://scan.coverity.com/projects/wodan58-moy)|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Moy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Moy?branch=master)|[![Codecov](https://codecov.io/gh/Wodan58/Moy/branch/master/graph/badge.svg)](https://codecov.io/gh/Wodan58/Moy)|[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Wodan58/Moy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Moy/context:cpp)|[![Alerts](https://img.shields.io/lgtm/alerts/g/Wodan58/Moy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Moy/alerts)

This project implements a variant of [Joy](https://github.com/Wodan58/joy1).
Conditions do not restore the stack to what it was before the condition
started. This project uses the
[BDW garbage collector](https://github.com/ivmai/bdwgc) and
[JAPI](https://github.com/maxstrauch/japi2-kernel).
JAPI is under the LGPL license, see LICENSE.txt

Changes
-------

Most builtins of Joy are supported in Moy.
Some other ones have been added: casting, fget, filetime, getch, identical,
in1, index, over, pick, poke, round, and sametype.
The build system requires new builtins in only one location: as a .c file in
the src-directory or the gui-directory.

Installation
------------

Run:

    cmake .
    cmake --build .

And:

    java -jar JAPI.jar &
    ./joy mandel.joy

This last test results in:

<img src="doc/mandel.jpg"/>

Mandelbrot in full Swing.
