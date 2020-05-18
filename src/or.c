/*
    module  : or.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef OR_C
#define OR_C

/**
or  :  X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
#define PROCEDURE	do_or
#define NAME		"or"
#define OPER1		|
#define OPER2		||
#include "andorxor.h"
#endif
