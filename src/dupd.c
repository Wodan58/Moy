/*
    module  : dupd.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_dupd(void)
{
    TRACE;
    stk++;
    stk[-1] = stk[-2];
    stk[-2] = stk[-3];
}
#else
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
