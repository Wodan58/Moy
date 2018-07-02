/*
    module  : conts.c
    version : 1.6
    date    : 07/02/18
*/

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
