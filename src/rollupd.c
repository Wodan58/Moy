/*
    module  : rollupd.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef ROLLUPD_X
#define ROLLUPD_C

#ifdef RUNTIME
void do_rollupd(void)
{
    node_t temp;

    TRACE;
    temp = stk[-2];
    stk[-2] = stk[-3];
    stk[-3] = stk[-4];
    stk[-4] = temp;
}
#else

#ifndef ROLLUP_C
#undef ROLLUP_X
#include "rollup.c"
#define ROLLUP_X
#endif

/**
rollupd  :  X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
#define PROCEDURE	do_rollupd
#define NAME		"rollupd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rollup
#include "dipped.h"
#endif
#endif
