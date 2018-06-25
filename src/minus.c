/*
    module  : minus.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
-  :  M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
#define PROCEDURE	do_minus
#define NAME		"-"
#define OPER		-
#include "plusminus.h"
/* minus.c */
