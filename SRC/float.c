/*
    module  : float.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
float  :  R  ->  B
Tests whether R is a float.
*/
#define PROCEDURE	do_float
#define NAME		"float"
#define REL		==
#define TYP		FLOAT_
#include "type.c"
