/*
    module  : set.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef SET_X
#define SET_C

#ifdef NEW_RUNTIME
void do_set(void)
{
    TRACE;
    do_push(0);
}
#else
/**
set  :  X  ->  B
Tests whether X is a set.
*/
#define PROCEDURE	do_set
#define NAME		"set"
#define REL		==
#define TYP		SET_
#include "type.h"
#endif
#endif
