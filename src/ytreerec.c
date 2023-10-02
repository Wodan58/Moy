/*
    module  : ytreerec.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef YTREEREC_C
#define YTREEREC_C

/**
OK 3160  (treerec)  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void ytreerec_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &list);	/* item on top of the stack */
    node = pvec_lst(env->stck);			/* 2nd item on the stack */
    if (node.op == LIST_) {			/* list = [[O] C] */

	prog(env, list.u.lis);			/* C */
	(void)pop(env);

	code(env, cons_);
	code(env, cons_);

	node.u.lis = 0;
	prime(env, node);

	node.u.proc = ytreerec_;
	node.op = ANON_PRIME_;
	prime(env, node);

	prime(env, list);			/* list = [[O] C] */
    } else {
	list = pvec_lst(list.u.lis);		/* list = [O] */
	prog(env, list.u.lis);
    }
}
#endif
