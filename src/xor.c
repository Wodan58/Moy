/*
    module  : xor.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_xor(void)
{
    TRACE;
    stk[-2] ^= stk[-1];
    stk--;
}
#else
/**
xor  :  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
#define PROCEDURE	do_xor
#define NAME		"xor"
#define OPER1		^
#define OPER2		!=
#include "andorxor.h"
#endif
