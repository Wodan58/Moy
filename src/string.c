/*
    module  : string.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
string  :  X  ->  B
Tests whether X is a string.
*/
#define PROCEDURE	do_string
#define NAME		"string"
#define REL		==
#define TYP		STRING_
#include "type.h"
