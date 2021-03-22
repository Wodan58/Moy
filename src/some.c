/*
    module  : some.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef SOME_C
#define SOME_C

/**
some  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
#define PROCEDURE	do_some
#define NAME		"some"
#define INITIAL		0
#define SOME
#include "someall.h"
#undef SOME
/* some.c */
#endif
