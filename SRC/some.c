/*
    module  : some.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
some  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
/* some.c */
#define PROCEDURE	some_
#define NAME		"some"
#define INITIAL		0
#include "someall.c"
