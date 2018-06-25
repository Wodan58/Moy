/*
    module  : integer.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
integer  :  X  ->  B
Tests whether X is an integer.
*/
#define PROCEDURE	do_integer
#define NAME		"integer"
#define REL		==
#define TYP		INTEGER_
#include "type.h"
