/*
    module  : ferror.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef FERROR_X
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
