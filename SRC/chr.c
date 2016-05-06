/*
    module  : chr.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
chr  :  I  ->  C
C is the character whose Ascii value is integer I (or logical or character).
*/
/* chr.c */
#define PROCEDURE	chr_
#define NAME		"chr"
#define RESULTTYP	CHAR_
#include "ordchr.c"
