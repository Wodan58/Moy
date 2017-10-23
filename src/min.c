/*
    module  : min.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
min  :  N1 N2  ->  N
N is the minimum of numeric values N1 and N2.  Also supports float.
*/
#define PROCEDURE	do_min
#define NAME		"min"
#define OPER		>
#include "maxmin.c"
