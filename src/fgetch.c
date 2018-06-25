/*
    module  : fgetch.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
#define PROCEDURE	do_fgetch
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_
#define EXPR		fgetc(stk->u.fil)
#include "fileget.h"
