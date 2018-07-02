/*
    module  : feof.c
    version : 1.5
    date    : 07/02/18
*/

/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(stk->u.fil)
#include "fileget.h"
