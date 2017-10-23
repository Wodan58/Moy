/*
    module  : chr.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
chr  :  I  ->  C
C is the character whose Ascii value is integer I (or logical or character).
*/
#define PROCEDURE	do_chr
#define NAME		"chr"
#define RESULTTYP	CHAR_
#include "ordchr.c"
