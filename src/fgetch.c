/*
    module  : fgetch.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef FGETCH_X
#define FGETCH_C

#ifdef NEW_RUNTIME
void do_fgetch(void)
{
    TRACE;
    do_push(fgetch((FILE *)stk[-1]));
}
#else
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
#endif
