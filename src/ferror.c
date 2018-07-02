/*
    module  : ferror.c
    version : 1.5
    date    : 07/02/18
*/

/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(stk->u.fil)
#include "fileget.h"
