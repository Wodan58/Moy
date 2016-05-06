/*
    module  : ftell.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
ftell  :  S  ->  S I
I is the current position of stream S.
*/
/* ftell.c */
#define PROCEDURE	ftell_
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_
#define EXPR		ftell(stk->u.fil)
#include "fileget.c"
