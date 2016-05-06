/*
    module  : ord.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
ord  :  C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
/* ord.c */
#define PROCEDURE	ord_
#define NAME		"ord"
#define RESULTTYP	INTEGER_
#include "ordchr.c"
