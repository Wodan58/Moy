/*
    module  : or.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
or  :  X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
/* or.c */
#define PROCEDURE	or_
#define NAME		"or"
#define OPER1		|
#define OPER2		||
#include "andorxor.c"
