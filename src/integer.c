/*
    module  : integer.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef INTEGER_X
#define INTEGER_C

#ifdef NEW_RUNTIME
void do_integer(void)
{
    TRACE;
    stk[-1] = IS_INTEGER(stk[-1]);
}
#else
/**
integer  :  X  ->  B
Tests whether X is an integer.
*/
#define PROCEDURE	do_integer
#define NAME		"integer"
#define REL		==
#define TYP		INTEGER_
#include "type.h"
#endif
#endif
