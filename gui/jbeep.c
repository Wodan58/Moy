/*
    module  : jbeep.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JBEEP_C
#define JBEEP_C

/**
jbeep  :  ->
Emits an audio beep.
*/
PRIVATE void do_jbeep(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    j_beep();
}
#endif
