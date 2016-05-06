/*
    module  : succ.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
succ  :  M  ->  N
Numeric N is the successor of numeric M.
*/
/* succ.c */
#define PROCEDURE	succ_
#define NAME		"succ"
#define OPER		+
#include "predsucc.c"
