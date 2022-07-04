/*
    module  : manual.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef MANUAL_C
#define MANUAL_C

#include "manual.h"

/**
manual  :  ->
Writes this manual of all Joy primitives to output file.
*/
PRIVATE void do_manual(pEnv env)
{
#ifdef COMPILING
    make_manual(0);
#endif
}
#endif
