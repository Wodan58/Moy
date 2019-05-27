/*
    module  : swapd.c
    version : 1.8
    date    : 05/26/19
*/
#ifndef SWAPD_X
#define SWAPD_C

#ifdef NEW_RUNTIME
void do_swapd(void)
{
    node_t temp;

    TRACE;
    temp = stk[-2];
    stk[-2] = stk[-3];
    stk[-3] = temp;
}
#else

#ifndef SWAP_C
#undef SWAP_X
#include "swap.c"
#define SWAP_X
#endif

/**
swapd  :  X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
#define PROCEDURE	do_swapd
#define NAME		"swapd"
#define PARAMCOUNT	THREEPARAMS
#define ARGUMENT	do_swap
#include "dipped.h"
#endif
#endif
