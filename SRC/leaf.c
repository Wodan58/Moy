/*
    module  : leaf.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
leaf  :  X  ->  B
Tests whether X is not a list.
*/
/* leaf.c */
#define PROCEDURE	leaf_
#define NAME		"leaf"
#define REL		!=
#define TYP		LIST_
#include "type.c"
