/*
    module  : echo.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
/* echo.c */
PUSH_PROC(echo_, INTEGER_, echoflag)
