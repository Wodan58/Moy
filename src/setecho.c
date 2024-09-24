/*
    module  : setecho.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef SETECHO_C
#define SETECHO_C

/**
Q0  IGNORE_POP  3000  setecho  :  D  I  ->
[IMPURE] Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
void setecho_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    env->echoflag = node.u.num;
}
#endif
