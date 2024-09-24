/*
    module  : fput.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef FPUT_C
#define FPUT_C

/**
Q0  OK  1940  fput  :  D  S X  ->  S
[FOREIGN] Writes X to stream S, pops X off stack.
*/
void fput_(pEnv env)
{
    Node elem, node;

    PARM(2, FPUT);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    if (elem.op == LIST_) {
	putc('[', node.u.fil);
	writeterm(env, elem.u.lis, node.u.fil);
	putc(']', node.u.fil);
    } else
	writefactor(env, elem, node.u.fil);
}
#endif
