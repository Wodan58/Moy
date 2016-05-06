/*
    module  : list.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
list  :  X  ->  B
Tests whether X is a list.
*/
/* list.c */
#define PROCEDURE	list_
#define NAME		"list"
#define REL		==
#define TYP		LIST_
#include "type.c"
