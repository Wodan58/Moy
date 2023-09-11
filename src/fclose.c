/*
    module  : fclose.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef FCLOSE_C
#define FCLOSE_C

/**
OK 1830  fclose  :  D	S  ->
Stream S is closed and removed from the stack.
*/
void fclose_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, FGET);
    node = lst_pop(env->stck);
    fclose(node.u.fil);
#endif
}
#endif
