/*
    module  : fclose.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    fclose(node.u.fil);
}
#endif
