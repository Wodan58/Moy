/*
    module  : in1.c
    version : 1.7
    date    : 03/15/21
*/
#ifndef IN1_C
#define IN1_C

/**
in1  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in1
#ifdef CORRECT_INHAS_COMPARE
#undef CORRECT_INHAS_COMPARE
#define CORRECT_INHAS_COMPARE_X
#endif
#define NAME		"in1"
#define AGGR		env->stk
#define ELEM		env->stk->next
#include "inhas.h"
#ifdef CORRECT_INHAS_COMPARE_X
#define CORRECT_INHAS_COMPARE
#endif
#endif
