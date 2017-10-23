/*
    module  : char.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
char  :  X  ->  B
Tests whether X is a character.
*/
#define PROCEDURE	do_char
#define NAME		"char"
#define REL		==
#define TYP		CHAR_
#include "type.c"
