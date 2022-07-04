/*
    module  : __html_manual.c
    version : 1.7
    date    : 06/20/22
*/
#ifndef __HTML_MANUAL_C
#define __HTML_MANUAL_C

#include "manual.h"

/**
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
PRIVATE void do___html_manual(pEnv env)
{
    COMPILE;
    make_manual(1);
}
/* __html_manual.c */
#endif
