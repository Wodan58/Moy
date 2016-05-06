/*
    module  : min.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
min  :  N1 N2  ->  N
N is the minimum of numeric values N1 and N2.  Also supports float.
*/
/* min.c */
#define PROCEDURE	min_
#define NAME		"min"
#define OPER		>
#include "maxmin.c"
