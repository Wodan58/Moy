/*
    module  : enconcat.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef ENCONCAT_C
#define ENCONCAT_C

/**
OK 2170  enconcat  :  DDDA 	X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
void enconcat_(pEnv env)
{
    PARM(3, CONCAT);
    swapd_(env);
    cons_(env);
    concat_(env);
}
#endif
