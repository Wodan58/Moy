/*
    module  : ord.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
ord  :  C  ->  I
Integer I is the Ascii value of character C (or logical or integer).
*/
#define PROCEDURE	do_ord
#define NAME		"ord"
#define RESULTTYP	INTEGER_
#include "ordchr.c"
