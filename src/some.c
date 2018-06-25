/*
    module  : some.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
some  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
#define PROCEDURE	do_some
#define NAME		"some"
#define INITIAL		0
#include "someall.h"
/* some.c */
