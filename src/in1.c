/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#include "runtime.h"

/**
in1  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in1
#define NAME		"in1"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.h"
