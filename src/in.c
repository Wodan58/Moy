/*
    module  : in.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef IN_C
#define IN_C

/**
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in
#define CORRECT_INHAS_COMPARE
#define NAME		"in"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.h"
#endif
