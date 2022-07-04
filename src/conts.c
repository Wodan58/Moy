/*
    module  : conts.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef CONTS_C
#define CONTS_C

/**
conts  :  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
PRIVATE void do_conts(pEnv env)
{
    PUSH_PTR(LIST_, 0);
}
#endif
