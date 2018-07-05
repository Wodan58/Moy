/*
    module  : float.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_float(void)
{
    float dbl;
    char buf[MAXSTR];

    TRACE;
    memcpy(&dbl, &stk[-1], sizeof(float));
    sprintf(buf, "%f", dbl);
    stk[-1] = strcmp(buf, "0.000000") && strcmp(buf, "nan");
}
#else
/**
float  :  R  ->  B
Tests whether R is a float.
*/
#define PROCEDURE	do_float
#define NAME		"float"
#define REL		==
#define TYP		FLOAT_
#include "type.h"
#endif
