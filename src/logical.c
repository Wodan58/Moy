/*
    module  : logical.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef LOGICAL_X
#define LOGICAL_C

#ifdef NEW_RUNTIME
void do_logical(void)
{
    TRACE;
    stk[-1] = !stk[-1] || stk[-1] == 1;
}
#else
/**
logical  :  X  ->  B
Tests whether X is a logical.
*/
#define PROCEDURE	do_logical
#define NAME		"logical"
#define REL		==
#define TYP		BOOLEAN_
#include "type.h"
#endif
#endif
