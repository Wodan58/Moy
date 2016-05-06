/*
    module  : logical.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
logical  :  X  ->  B
Tests whether X is a logical.
*/
/* logical.c */
#define PROCEDURE	logical_
#define NAME		"logical"
#define REL		==
#define TYP		BOOLEAN_
#include "type.c"
