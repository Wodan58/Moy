/*
    module  : feof.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
/* feof.c */
#define PROCEDURE	feof_
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(stk->u.fil)
#include "fileget.c"
