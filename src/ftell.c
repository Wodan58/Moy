/*
    module  : ftell.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
ftell  :  S  ->  S I
I is the current position of stream S.
*/
#define PROCEDURE	do_ftell
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_
#define EXPR		ftell(stk->u.fil)
#include "fileget.h"
