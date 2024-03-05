/*
    module  : getch.c
    version : 1.12
    date    : 03/05/24
*/
#ifndef GETCH_C
#define GETCH_C

/**
Q0  OK  3160  getch  :  A  ->  N
[IMPURE] Reads a character from input and puts it onto stack.
*/
void getch_(pEnv env)
{
    static unsigned char init;
    Node node;

    if (env->ignore) {
	node.u.num = 0;
	node.op = CHAR_;
	env->stck = pvec_add(env->stck, node);
	return;
    }
    node.u.num = get_input();
    if (!init) {
	if (node.u.num == '\n')
	    node.u.num = get_input();		/* skip first newline */
	init = 1;
    }
    node.op = CHAR_;
    env->stck = pvec_add(env->stck, node);
}
#endif
