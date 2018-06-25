/*
    module  : ferror.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(stk->u.fil)
#include "fileget.h"
