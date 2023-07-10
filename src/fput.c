/*
    module  : fput.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FPUT_C
#define FPUT_C

/**
OK 1950  fput  :  DDA	S X  ->  S
Writes X to stream S, pops X off stack.
*/
void fput_(pEnv env)
{
    int stdout_dup;
    Node node, elem;

    PARM(2, FPUT);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    fflush(stdout);
    if ((stdout_dup = dup(1)) != -1)
        dup2(fileno(node.u.fil), 1);
    if (elem.op == LIST_) {
        putchar('[');
        writeterm(env, elem.u.lis);
        putchar(']');
    } else
        writefactor(env, elem);
    putchar(' ');
    fflush(stdout);
    if (stdout_dup != -1) {
        dup2(stdout_dup, 1);
        close(stdout_dup);
    }
}
#endif
