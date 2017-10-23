/*
    module  : set.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
set  :  X  ->  B
Tests whether X is a set.
*/
#define PROCEDURE	do_set
#define NAME		"set"
#define REL		==
#define TYP		SET_
#include "type.c"
