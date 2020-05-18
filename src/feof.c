/*
    module  : feof.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef FEOF_C
#define FEOF_C

/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
#define PROCEDURE	do_feof
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		feof(stk->u.fil)
#include "fileget.h"
#endif
