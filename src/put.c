/*
    module  : put.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef PUT_C
#define PUT_C

/**
OK 3080  put  :  D 	X  ->
Writes X to output, pops X off stack.
*/
void put_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    if (node.op == LIST_) {
	putchar('[');
	writeterm(env, node.u.lis, stdout);
	putchar(']');
    } else
	writefactor(env, node, stdout);
    putchar(' ');
}
#endif
