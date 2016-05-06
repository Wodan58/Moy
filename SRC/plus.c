/*
    module  : plus.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
+  :  M I  ->  N
Numeric N is the result of adding integer I to numeric M.
Also supports float.
*/
/* plus.c */
#define PROCEDURE	plus_
#define NAME		"+"
#define OPER		+
#include "plusminus.c"
