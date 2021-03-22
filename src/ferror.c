/*
    module  : ferror.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef FERROR_C
#define FERROR_C

/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(env->stk->u.fil)
#include "fileget.h"
#endif
