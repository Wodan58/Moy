/*
    module  : rolldownd.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef ROLLDOWND_X
#define ROLLDOWND_C

#ifdef NEW_RUNTIME
void do_rolldownd(void)
{
    node_t temp;

    TRACE;
    temp = stk[-4];
    stk[-4] = stk[-3];
    stk[-3] = stk[-2];
    stk[-2] = temp;
}
#else
#ifndef ROLLDOWN_C
#undef ROLLDOWN_X
#include "rolldown.c"
#define ROLLDOWN_X
#endif

/**
rolldownd  :  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
#define PROCEDURE	do_rolldownd
#define NAME		"rolldownd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rolldown
#include "dipped.h"
#endif
#endif
