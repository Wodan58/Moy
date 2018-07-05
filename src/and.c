/*
    module  : and.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_and(void)
{
    TRACE;
    stk[-2] &= stk[-1];
    stk--;
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
