/*
    module  : popd.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef POPD_X
#define POPD_C

#ifdef NEW_RUNTIME
void do_popd(void)
{
    TRACE;
    stk[-2] = stk[-1];
    (void)do_pop();
}
#else

#ifndef POP_C
#include "pop.c"
#define POP_X
#endif

/**
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
#define PROCEDURE	do_popd
#define NAME		"popd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	do_pop
#include "dipped.h"
#endif
#endif
