/*
    module  : popd.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_popd(void)
{
    TRACE;
    stk[-2] = stk[-1];
    stk--;
}
#else
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
