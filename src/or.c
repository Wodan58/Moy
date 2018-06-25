/*
    module  : or.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
or  :  X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
#define PROCEDURE	do_or
#define NAME		"or"
#define OPER1		|
#define OPER2		||
#include "andorxor.h"
