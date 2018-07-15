/*
    module  : char.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef CHAR_X
#define CHAR_C

#ifdef NEW_RUNTIME
void do_char(void)
{
    TRACE;
    stk[-1] = stk[-1] >= ' ' && stk[-1] <= '~';
}
#else
/**
char  :  X  ->  B
Tests whether X is a character.
*/
#define PROCEDURE	do_char
#define NAME		"char"
#define REL		==
#define TYP		CHAR_
#include "type.h"
#endif
#endif
