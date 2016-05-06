/*
    module  : and.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
and  :  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
/* and.c */
#define PROCEDURE	and_
#define NAME		"and"
#define OPER1		&
#define OPER2		&&
#include "andorxor.c"
