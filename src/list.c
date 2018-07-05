/*
    module  : list.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_list(void)
{
    TRACE;
    stk[-1] = stk[-1] > start_of_heap;
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
