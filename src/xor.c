/*
    module  : xor.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef XOR_C
#define XOR_C

/**
xor  :  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
#define PROCEDURE	do_xor
#define NAME		"xor"
#define OPER1		^
#define OPER2		!=
#include "andorxor.h"
#endif
