/*
    module  : logical.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
logical  :  X  ->  B
Tests whether X is a logical.
*/
#define PROCEDURE	do_logical
#define NAME		"logical"
#define REL		==
#define TYP		BOOLEAN_
#include "type.h"
