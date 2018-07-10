/*
    module  : fgetch.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef FGETCH_X
#define FGETCH_C

/**
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
#define PROCEDURE	do_fgetch
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_
#define EXPR		fgetc(stk->u.fil)
#include "fileget.h"
#endif
