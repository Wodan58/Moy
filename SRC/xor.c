/*
    module  : xor.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
xor  :  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
/* xor.c */
#define PROCEDURE	xor_
#define NAME		"xor"
#define OPER1		^
#define OPER2		!=
#include "andorxor.c"
