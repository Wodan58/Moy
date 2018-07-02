/*
    module  : ftell.c
    version : 1.5
    date    : 07/02/18
*/

/**
ftell  :  S  ->  S I
I is the current position of stream S.
*/
#define PROCEDURE	do_ftell
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_
#define EXPR		ftell(stk->u.fil)
#include "fileget.h"
