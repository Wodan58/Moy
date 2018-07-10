/*
    module  : __html_manual.c
    version : 1.3
    date    : 07/10/18
*/
#ifndef __HTML_MANUAL_X
#define __HTML_MANUAL_C

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

#ifndef MANUAL_C
#undef MANUAL_X
#include "manual.c"
#define MANUAL_X
#endif

/**
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
PRIVATE void do___html_manual(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    make_manual(1);
}
#endif
