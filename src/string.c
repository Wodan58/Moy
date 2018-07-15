/*
    module  : string.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef STRING_X
#define STRING_C

#ifdef NEW_RUNTIME
void do_string(void)
{
    TRACE;
    stk[-1] = IS_STRING(stk[-1]);
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
