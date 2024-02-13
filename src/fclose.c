/*
    module  : fclose.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
OK 1830  fclose  :  D	S  ->
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
