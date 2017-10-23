/*
    module  : pred.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
pred  :  M  ->  N
Numeric N is the predecessor of numeric M.
*/
#define PROCEDURE	do_pred
#define NAME		"pred"
#define OPER		-
#include "predsucc.c"
