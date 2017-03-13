/*
    module  : succ.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
succ  :  M  ->  N
Numeric N is the successor of numeric M.
*/
#define PROCEDURE	do_succ
#define NAME		"succ"
#define OPER		+
#include "predsucc.c"
