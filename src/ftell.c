/*
    module  : ftell.c
    version : 1.8
    date    : 03/28/20
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
#define EXPR		ftell(stk->u.fil)
#include "fileget.h"
#endif
