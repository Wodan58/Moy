/*
    module  : fclose.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
Q0  OK  1830  fclose  :  D  S  ->
[FOREIGN] Stream S is closed and removed from the stack.
*/
void fclose_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    env->stck = pvec_pop(env->stck, &node);
    fclose(node.u.fil);
}
#endif
