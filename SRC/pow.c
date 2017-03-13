/*
    module  : pow.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
pow  :  F G  ->  H
H is F raised to the Gth power.
*/
#define PROCEDURE	do_pow
#define NAME		"pow"
#define FUNC		pow
#include "bfloat.c"
