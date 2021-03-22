/*
    module  : ftell.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef FTELL_C
#define FTELL_C

/**
ftell  :  S  ->  S I
I is the current position of stream S.
*/
#define PROCEDURE	do_ftell
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_
#define EXPR		ftell(env->stk->u.fil)
#include "fileget.h"
#endif
