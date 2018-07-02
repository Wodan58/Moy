/*
    module  : in1.c
    version : 1.1
    date    : 07/02/18
*/

/**
in1  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
#define PROCEDURE	do_in1
#define NAME		"in1"
#define AGGR		stk
#define ELEM		stk->next
#include "inhas.h"
