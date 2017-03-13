/*
    module  : feof.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(stk->u.fil)
#include "fileget.c"
