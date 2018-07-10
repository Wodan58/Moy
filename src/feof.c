/*
    module  : feof.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef FEOF_X
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
