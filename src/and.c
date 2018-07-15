/*
    module  : and.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef AND_X
#define AND_C

#ifdef NEW_RUNTIME
void do_and(void)
{
    TRACE;
    stk[-2] &= stk[-1];
    (void)do_pop();
}
#else
/**
and  :  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
#define PROCEDURE	do_and
#define NAME		"and"
#define OPER1		&
#define OPER2		&&
#include "andorxor.h"
#endif
#endif
