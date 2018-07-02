/*
    module  : has.c
    version : 1.5
    date    : 07/02/18
*/

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
