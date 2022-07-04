/*
    module  : fgetch.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
#define PROCEDURE	do_fgetch
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_NEWNODE
#define EXPR		fgetc(env->stk->u.fil)
#include "fileget.h"
/* fgetch.c */
#endif
