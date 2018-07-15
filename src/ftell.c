/*
    module  : ftell.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef FTELL_X
#define FTELL_C

#ifdef NEW_RUNTIME
void do_feof(void)
{
    TRACE;
    do_push(ftell((FILE *)stk[-1]));
}
#else
/**
ftell  :  S  ->  S I
I is the current position of stream S.
*/
#define PROCEDURE	do_ftell
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_
#define EXPR		ftell(stk->u.fil)
#include "fileget.h"
#endif
#endif
