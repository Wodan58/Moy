/*
    module  : setecho.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef SETECHO_C
#define SETECHO_C

/**
OK 3020  setecho  :  D	I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
void setecho_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    env->echoflag = node.u.num;
}
#endif
