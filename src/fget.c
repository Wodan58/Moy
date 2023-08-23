/*
    module  : fget.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef FGET_C
#define FGET_C

/**
OK 1870  fget  :  DAA	S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
void fget_(pEnv env)
{
    Node node;
    int stdin_dup;

    PARM(1, FGET);
    node = lst_back(env->stck);
    if ((stdin_dup = dup(0)) != -1)
        dup2(fileno(node.u.fil), 0);
    env->token = yylex(env);
    readfactor(env);
    if (stdin_dup != -1) {
        dup2(stdin_dup, 0);
        close(stdin_dup);
    }
}
#endif
