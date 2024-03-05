/*
    module  : put.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef PUT_C
#define PUT_C

/**
Q0  OK  3080  put  :  D  X  ->
[IMPURE] Writes X to output, pops X off stack.
*/
void put_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    if (env->ignore)
	return;
    if (node.op == LIST_) {
	putchar('[');
	writeterm(env, node.u.lis, stdout);
	putchar(']');
    } else
	writefactor(env, node, stdout);
    putchar(' ');
}
#endif
