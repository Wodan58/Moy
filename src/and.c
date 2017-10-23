/*
    module  : and.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
and  :  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
#define PROCEDURE	do_and
#define NAME		"and"
#define OPER1		&
#define OPER2		&&
#include "andorxor.c"
