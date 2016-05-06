/*
    module  : minus.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
-  :  M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
/* minus.c */
#define PROCEDURE	minus_
#define NAME		"-"
#define OPER		-
#include "plusminus.c"
