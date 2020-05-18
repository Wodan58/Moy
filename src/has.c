/*
    module  : has.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef HAS_C
#define HAS_C

/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has
#define CORRECT_INHAS_COMPARE
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "inhas.h"
#endif
