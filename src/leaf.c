/*
    module  : leaf.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef LEAF_X
#define LEAF_C

#ifdef RUNTIME
void do_leaf(void)
{
    TRACE;
    stk[-1] = stk[-1] < start_of_heap;
}
#else
/**
leaf  :  X  ->  B
Tests whether X is not a list.
*/
#define PROCEDURE	do_leaf
#define NAME		"leaf"
#define REL		!=
#define TYP		LIST_
#include "type.h"
#endif
#endif
