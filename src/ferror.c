/*
    module  : ferror.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef FERROR_X
#define FERROR_C

#ifdef NEW_RUNTIME
void do_ferror(void)
{
    TRACE;
    do_push(ferror((FILE *)stk[-1]));
}
#else
/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(stk->u.fil)
#include "fileget.h"
#endif
#endif
