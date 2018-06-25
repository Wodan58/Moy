/*
    module  : leaf.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
leaf  :  X  ->  B
Tests whether X is not a list.
*/
#define PROCEDURE	do_leaf
#define NAME		"leaf"
#define REL		!=
#define TYP		LIST_
#include "type.h"
