/*
    module  : put.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef PUT_C
#define PUT_C

/**
OK 3110  put  :  D 	X  ->
Writes X to output, pops X off stack.
*/
void put_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    if (node.op == LIST_) {
        putchar('[');
        writeterm(env, node.u.lis);
        putchar(']');
    } else
        writefactor(env, node);
    putchar(' ');
}
#endif
