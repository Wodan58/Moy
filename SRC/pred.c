/*
    module  : pred.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
pred  :  M  ->  N
Numeric N is the predecessor of numeric M.
*/
/* pred.c */
#define PROCEDURE	pred_
#define NAME		"pred"
#define OPER		-
#include "predsucc.c"
