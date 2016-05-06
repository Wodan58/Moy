/*
    module  : integer.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
integer  :  X  ->  B
Tests whether X is an integer.
*/
/* integer.c */
#define PROCEDURE	integer_
#define NAME		"integer"
#define REL		==
#define TYP		INTEGER_
#include "type.c"
