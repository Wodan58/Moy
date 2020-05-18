/*
    module  : conts.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef CONTS_C
#define CONTS_C

/**
conts  :  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
PRIVATE void do_conts(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
#endif
