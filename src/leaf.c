/*
    module  : leaf.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
leaf  :  X  ->  B
Tests whether X is not a list.
*/
#define PROCEDURE	do_leaf
#define NAME		"leaf"
#define REL		!=
#define TYP		LIST_
#include "type.c"
