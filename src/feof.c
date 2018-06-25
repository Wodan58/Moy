/*
    module  : feof.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(stk->u.fil)
#include "fileget.h"
