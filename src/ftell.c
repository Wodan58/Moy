/*
    module  : ftell.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef FTELL_X
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
