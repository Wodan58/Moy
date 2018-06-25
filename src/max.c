/*
    module  : max.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
max  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.  Also supports float.
*/
#define PROCEDURE	do_max
#define NAME		"max"
#define OPER		<
#include "maxmin.h"
/* max.c */
