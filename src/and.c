/*
    module  : and.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef AND_C
#define AND_C

/**
and  :  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
#define PROCEDURE	do_and
#define NAME		"and"
#define OPER1		&
#define OPER2		&&
#include "andorxor.h"
#endif
