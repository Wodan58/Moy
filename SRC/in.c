/*
    module  : in.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
/* in.c */
#define PROCEDURE	in_
#define NAME		"in"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.c"
