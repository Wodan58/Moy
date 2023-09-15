/*
    module  : fput.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef FPUT_C
#define FPUT_C

/**
OK 1940  fput  :  D	S X  ->  S
Writes X to stream S, pops X off stack.
*/
void fput_(pEnv env)
{
    FILE *fp;
    Node node, elem;

    PARM(2, FPUT);
    elem = lst_pop(env->stck);
    node = lst_back(env->stck);
    fp = node.u.fil;
    if (elem.op == LIST_) {
	putc('[', fp);
	writeterm(env, elem.u.lis, fp);
	putc(']', fp);
    } else
	writefactor(env, elem, fp);
    putc(' ', fp);
}
#endif
