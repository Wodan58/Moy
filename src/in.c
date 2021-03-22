/*
    module  : in.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef IN_C
#define IN_C

#ifdef CASE_X
#undef CASE_X
#undef CASE_C
#endif

#include "case.c"

/**
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in
#define CORRECT_INHAS_COMPARE
#define NAME		"in"
#define AGGR		env->stk
#define ELEM		env->stk->next
#include "inhas.h"
#endif
