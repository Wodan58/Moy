/*
    module  : fgetch.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
/* fgetch.c */
#define PROCEDURE	fgetch_
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_
#define EXPR		fgetc(stk->u.fil)
#include "fileget.c"
