/*
    module  : has.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef HAS_C
#define HAS_C

/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has
#define NAME		"has"
#define AGGR		env->stk->next
#define ELEM		env->stk
#include "inhas.h"
/* has.c */
#endif
