/*
    module  : in.c
    version : 1.5
    date    : 06/29/18
*/
#include "runtime.h"

/**
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in
#define CORRECT_INHAS_COMPARE
#define NAME		"in"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.h"
