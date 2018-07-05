/*
    module  : string.c
    version : 1.5
    date    : 07/05/18
*/
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
