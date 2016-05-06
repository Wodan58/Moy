/*
    module  : iflogical.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
iflogical  :  X [T] [E]  ->  ...
If X is a logical or truth value, executes T else executes E.
*/
/* iflogical.c */
#define PROCEDURE	iflogical_
#define NAME		"iflogical"
#define TYP		BOOLEAN_
#include "if_type.c"
