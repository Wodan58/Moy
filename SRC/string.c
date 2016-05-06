/*
    module  : string.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
string  :  X  ->  B
Tests whether X is a string.
*/
/* string.c */
#define PROCEDURE	string_
#define NAME		"string"
#define REL		==
#define TYP		STRING_
#include "type.c"

#undef PROCEDURE
#undef NAME
#undef REL
#undef TYP
