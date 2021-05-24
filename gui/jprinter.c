/*
    module  : jprinter.c
    version : 1.1
    date    : 04/28/21
*/
#ifndef JPRINTER_C
#define JPRINTER_C

/**
jprinter  :  frame  ->  event
Creates a new object, representing a paper of the printer and returns its
event number. On error -1 will be returned. A printer object can be used like a
canvas where all drawing functions will be passed to the printer instead of a
window. A printer generates no event.
*/
PRIVATE void do_jprinter(pEnv env)
{
    int frame;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(__func__);
    INTEGER(__func__);
    frame = env->stk->u.num;
    POP(env->stk);
    env->stk->u.num = j_printer(frame);
}
#endif
