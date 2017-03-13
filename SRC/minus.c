/*
    module  : minus.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
-  :  M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
#define PROCEDURE	do_minus
#define NAME		"-"
#define OPER		-
#include "plusminus.c"
