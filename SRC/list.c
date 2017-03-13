/*
    module  : list.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
list  :  X  ->  B
Tests whether X is a list.
*/
#define PROCEDURE	do_list
#define NAME		"list"
#define REL		==
#define TYP		LIST_
#include "type.c"
