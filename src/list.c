/*
    module  : list.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
list  :  X  ->  B
Tests whether X is a list.
*/
#define PROCEDURE	do_list
#define NAME		"list"
#define REL		==
#define TYP		LIST_
#include "type.h"
