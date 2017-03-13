/*
    module  : max.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
max  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.  Also supports float.
*/
#define PROCEDURE	do_max
#define NAME		"max"
#define OPER		<
#include "maxmin.c"
