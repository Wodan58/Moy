/*
    module  : or.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_or(void)
{
    TRACE;
    stk[-2] |= stk[-1];
    stk--;
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
