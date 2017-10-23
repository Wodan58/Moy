/*
    module  : in.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in
#define NAME		"in"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.c"
