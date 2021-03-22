/*
    module  : has.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef HAS_C
#define HAS_C

#ifdef CASE_X
#undef CASE_X
#undef CASE_C
#endif

#include "case.c"

/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has
#define CORRECT_INHAS_COMPARE
#define NAME		"has"
#define AGGR		env->stk->next
#define ELEM		env->stk
#include "inhas.h"
#endif
