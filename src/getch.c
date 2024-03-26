/*
    module  : getch.c
    version : 1.13
    date    : 03/21/24
*/
#ifndef GETCH_C
#define GETCH_C

/**
Q0  POSTPONE  3160  getch  :  A  ->  N
[IMPURE] Reads a character from input and puts it onto stack.
*/
void getch_(pEnv env)
{
    static unsigned char init;
    Node node;

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
