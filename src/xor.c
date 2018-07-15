/*
    module  : xor.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef XOR_X
#define XOR_C

#ifdef NEW_RUNTIME
void do_xor(void)
{
    TRACE;
    stk[-2] ^= stk[-1];
    (void)do_pop();
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
#endif
