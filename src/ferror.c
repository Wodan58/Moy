/*
    module  : ferror.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef FERROR_C
#define FERROR_C

/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
#define PROCEDURE	do_ferror
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		ferror(stk->u.fil)
#include "fileget.h"
#endif
