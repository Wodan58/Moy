/*
    module  : conts.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef CONTS_X
#define CONTS_C

/**
conts  :  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
PRIVATE void do_conts(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
#endif
