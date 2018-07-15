/*
    module  : feof.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef FEOF_X
#define FEOF_C

#ifdef NEW_RUNTIME
void do_feof(void)
{
    TRACE;
    do_push(feof((FILE *)stk[-1]));
}
#else
/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(stk->u.fil)
#include "fileget.h"
#endif
#endif
