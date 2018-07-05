/*
    module  : swapd.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_swapd(void)
{
    node_t temp;

    TRACE;
    temp = stk[-2];
    stk[-2] = stk[-3];
    stk[-3] = temp;
}
#else
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
