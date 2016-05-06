/*
    module  : system.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
system  :  "command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
/* system.c */
USETOP(system_, "system", STRING, system(stk->u.str))
