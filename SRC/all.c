/*
    module  : all.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
all  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
/* all.c */
#define PROCEDURE	all_
#define NAME		"all"
#define INITIAL		1
#include "someall.c"
