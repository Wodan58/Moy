/*
    module  : has.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
#define PROCEDURE	do_has
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "inhas.c"
