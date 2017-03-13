/*
    module  : ferror.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(stk->u.fil)
#include "fileget.c"
