/*
    module  : __html_manual.c
    version : 1.4
    date    : 09/15/23
*/
#ifndef __HTML_MANUAL_C
#define __HTML_MANUAL_C

#include "manual.h"

/**
OK 2940  __html_manual  :  N	->
Writes this manual of all Joy primitives to output file in HTML style.
*/
void __html_manual_(pEnv env)
{
    make_manual(1);
    /* nothing */
}
#endif
