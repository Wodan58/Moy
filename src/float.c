/*
    module  : float.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
float  :  R  ->  B
Tests whether R is a float.
*/
#define PROCEDURE	do_float
#define NAME		"float"
#define REL		==
#define TYP		FLOAT_
#include "type.h"
