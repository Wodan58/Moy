/*
    module  : string.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
string  :  X  ->  B
Tests whether X is a string.
*/
#define PROCEDURE	do_string
#define NAME		"string"
#define REL		==
#define TYP		STRING_
#include "type.c"
