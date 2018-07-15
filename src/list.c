/*
    module  : list.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef LIST_X
#define LIST_C

#ifdef NEW_RUNTIME
void do_list(void)
{
    TRACE;
    stk[-1] = IS_LIST(stk[-1]);
}
#else
/**
list  :  X  ->  B
Tests whether X is a list.
*/
#define PROCEDURE	do_list
#define NAME		"list"
#define REL		==
#define TYP		LIST_
#include "type.h"
#endif
#endif
