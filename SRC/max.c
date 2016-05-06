/*
    module  : max.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
max  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.  Also supports float.
*/
/* max.c */
#define PROCEDURE	max_
#define NAME		"max"
#define OPER		<
#include "maxmin.c"
