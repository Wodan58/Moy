/*
    module  : fgetch.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
#define PROCEDURE	do_fgetch
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_
#define EXPR		fgetc(env->stk->u.fil)
#include "fileget.h"
#endif
