/*
    module  : in.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef IN_C
#define IN_C

/**
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in
#define NAME		"in"
#define AGGR		env->stk
#define ELEM		env->stk->next
#include "inhas.h"
/* in.c */
#endif
