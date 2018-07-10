/*
    module  : integer.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef INTEGER_X
#define INTEGER_C

#ifdef RUNTIME
void do_integer(void)
{
    TRACE;
    stk[-1] = stk[-1] && abs(stk[-1]) < start_of_data;
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
