/*
    module  : and.c
    version : 1.4
    date    : 07/02/18
*/

/**
and  :  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
#define PROCEDURE	do_and
#define NAME		"and"
#define OPER1		&
#define OPER2		&&
#include "andorxor.h"
