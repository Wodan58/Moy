/*
    module  : has.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "inhas.h"
