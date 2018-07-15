/*
    module  : conts.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef CONTS_X
#define CONTS_C

#ifdef NEW_VERSION
void do_conts(void)
{
    TRACE;
    do_push(0);
}
#else
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
#endif
