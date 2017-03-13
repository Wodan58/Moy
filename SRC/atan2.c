/*
    module  : atan2.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
atan2  :  F G  ->  H
H is the arc tangent of F / G.
*/
#define PROCEDURE	do_atan2
#define NAME		"atan2"
#define FUNC		atan2
#include "bfloat.c"
