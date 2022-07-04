/*
    module  : feof.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef FEOF_C
#define FEOF_C

/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_NEWNODE
#define EXPR		feof(env->stk->u.fil)
#include "fileget.h"
/* feof.c */
#endif
