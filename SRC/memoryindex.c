/*
    module  : memoryindex.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
__memoryindex  :  ->
Pushes current value of memory.
*/
/* memoryindex.c */
PUSH_PROC(__memoryindex_, INTEGER_, (stk > memory && stk < &memory[MEMORYMAX] ?  stk - memory : 0))
