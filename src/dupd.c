/*
    module  : dupd.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef DUPD_X
#define DUPD_C

#ifdef NEW_RUNTIME
void do_dupd(void)
{
    TRACE;
    do_push(stk[-1]);
    stk[-2] = stk[-3];
}
#else

#ifndef DUP_C
#include "dup.c"
#define DUP_X
#endif

/**
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
#define PROCEDURE	do_dupd
#define NAME		"dupd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_dup
#include "dipped.h"
#endif
#endif
