/*
    module  : ferror.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef FERROR_C
#define FERROR_C

/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define EXPR		ferror(env->stk->u.fil)
#include "fileget.h"
/* ferror.c */
#endif
