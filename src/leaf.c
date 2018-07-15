/*
    module  : leaf.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef LEAF_X
#define LEAF_C

#ifdef NEW_RUNTIME
void do_leaf(void)
{
    TRACE;
    stk[-1] = !IS_LIST(stk[-1]);
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
