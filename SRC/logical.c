/*
    module  : logical.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
logical  :  X  ->  B
Tests whether X is a logical.
*/
#define PROCEDURE	do_logical
#define NAME		"logical"
#define REL		==
#define TYP		BOOLEAN_
#include "type.c"
