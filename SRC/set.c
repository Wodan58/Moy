/*
    module  : set.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
set  :  X  ->  B
Tests whether X is a set.
*/
/* set.c */
#define PROCEDURE	set_
#define NAME		"set"
#define REL		==
#define TYP		SET_
#include "type.c"
