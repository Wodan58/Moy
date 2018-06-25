/*
    module  : iflogical.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
iflogical  :  X [T] [E]  ->  ...
If X is a logical or truth value, executes T else executes E.
*/
#define PROCEDURE	do_iflogical
#define NAME		"iflogical"
#define TYP		BOOLEAN_
#include "iftype.h"
/* iflogical.c */
