/*
    module  : all.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
all  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
#define PROCEDURE	do_all
#define NAME		"all"
#define INITIAL		1
#include "someall.h"
/* all.c */
