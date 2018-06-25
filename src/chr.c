/*
    module  : chr.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
chr  :  I  ->  C
C is the character whose Ascii value is integer I (or logical or character).
*/
#define PROCEDURE	do_chr
#define NAME		"chr"
#define RESULTTYP	CHAR_
#include "ordchr.h"
/* chr.c */
