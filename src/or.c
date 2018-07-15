/*
    module  : or.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef OR_X
#define OR_C

#ifdef NEW_RUNTIME
void do_or(void)
{
    TRACE;
    stk[-2] |= stk[-1];
    (void)do_pop();
}
#else
/**
or  :  X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
#define PROCEDURE	do_or
#define NAME		"or"
#define OPER1		|
#define OPER2		||
#include "andorxor.h"
#endif
#endif
