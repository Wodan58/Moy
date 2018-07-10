/*
    module  : string.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef STRING_X
#define STRING_C

#ifdef RUNTIME
void do_string(void)
{
    TRACE;
    stk[-1] = stk[-1] > start_of_data && stk[-1] < start_of_heap;
}
#else
/**
string  :  X  ->  B
Tests whether X is a string.
*/
#define PROCEDURE	do_string
#define NAME		"string"
#define REL		==
#define TYP		STRING_
#include "type.h"
#endif
#endif
