/*
    module  : fclose.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
OK 1830  fclose  :  D	S  ->
Stream S is closed and removed from the stack.
*/
void fclose_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    env->stck = pvec_pop(env->stck, &node);
    fclose(node.u.fil);
}
#endif
