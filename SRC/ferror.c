/*
    module  : ferror.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
ferror  :  S  ->  S B
B is the error status of stream S.
*/
/* ferror.c */
#define PROCEDURE	ferror_
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(stk->u.fil)
#include "fileget.c"
