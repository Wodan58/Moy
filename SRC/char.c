/*
    module  : char.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
char  :  X  ->  B
Tests whether X is a character.
*/
/* char.c */
#define PROCEDURE	char_
#define NAME		"char"
#define REL		==
#define TYP		CHAR_
#include "type.c"
