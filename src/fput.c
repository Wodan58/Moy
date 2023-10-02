/*
    module  : fput.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FPUT_C
#define FPUT_C

/**
OK 1940  fput  :  D	S X  ->  S
Writes X to stream S, pops X off stack.
*/
void fput_(pEnv env)
{
    Node node, elem;

    PARM(2, FPUT);
    env->stck = pvec_pop(env->stck, &elem);
    node = pvec_lst(env->stck);
    if (elem.op == LIST_) {
	putc('[', node.u.fil);
	writeterm(env, elem.u.lis, node.u.fil);
	putc(']', node.u.fil);
    } else
	writefactor(env, elem, node.u.fil);
    putc(' ', node.u.fil);
}
#endif
