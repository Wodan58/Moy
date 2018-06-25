/*
    module  : char.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
char  :  X  ->  B
Tests whether X is a character.
*/
#define PROCEDURE	do_char
#define NAME		"char"
#define REL		==
#define TYP		CHAR_
#include "type.h"
