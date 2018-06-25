/*
    module  : __latex_manual.c
    version : 1.1
    date    : 06/25/18
*/
#include "runtime.h"

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

/**
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
PRIVATE void do___latex_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(2);
}
