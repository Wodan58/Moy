/*
    module  : conts.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef CONTS_C
#define CONTS_C

/**
conts  :  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
PRIVATE void do_conts(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_PTR(LIST_, 0);
}
#endif
