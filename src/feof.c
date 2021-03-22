/*
    module  : feof.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef FEOF_C
#define FEOF_C

/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(env->stk->u.fil)
#include "fileget.h"
#endif
