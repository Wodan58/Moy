/*
    module  : has.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
/* has.c */
#define PROCEDURE	has_
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "inhas.c"
