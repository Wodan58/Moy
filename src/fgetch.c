/*
    module  : fgetch.c
    version : 1.5
    date    : 07/02/18
*/

/**
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
#define PROCEDURE	do_fgetch
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_
#define EXPR		fgetc(stk->u.fil)
#include "fileget.h"
