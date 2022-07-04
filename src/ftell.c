/*
    module  : ftell.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef FTELL_C
#define FTELL_C

/**
ftell  :  S  ->  S I
I is the current position of stream S.
*/
#define PROCEDURE	do_ftell
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_NEWNODE
#define EXPR		ftell(env->stk->u.fil)
#include "fileget.h"
/* ftell.c */
#endif
