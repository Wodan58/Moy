/*
    module  : set.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
set  :  X  ->  B
Tests whether X is a set.
*/
#define PROCEDURE	do_set
#define NAME		"set"
#define REL		==
#define TYP		SET_
#include "type.h"
