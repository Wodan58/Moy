/*
    module  : treegenrecaux.c
    version : 1.13
    date    : 03/05/24
*/
#ifndef TREEGENRECAUX_C
#define TREEGENRECAUX_C

/**
Q1  OK  3300  #treegenrec  :  DDDDDA  T [[O1] [O2] C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void treegenrecaux_(pEnv env)
{
    unsigned size;
    Node list, node;

    PARM(1, DIP);
    env->stck = pvec_pop(env->stck, &list);	/* item on top of the stack */
    node = pvec_lst(env->stck);			/* 2nd item on the stack */
    if (node.op == LIST_) {			/* list = [[O1] [O2] C] */
	prog(env, list.u.lis);			/* C */
	(void)pop(env);
	(void)pop(env);

	code(env, cons_);
	code(env, cons_);

	node.u.lis = 0;
	prime(env, node);

	node.u.proc = treegenrecaux_;
	node.op = ANON_PRIME_;
	prime(env, node);

	env->prog = pvec_add(env->prog, list);	/* list = [[O1] [O2] C] */

	size = pvec_cnt(list.u.lis);		/* list = [[O1] [O2] C] */
	list = pvec_nth(list.u.lis, size - 2);	/* list = [O2] */
	prog(env, list.u.lis);
    } else {					/* list = [[O1] [O2] C] */
	list = pvec_lst(list.u.lis);		/* list = [O1] */
	prog(env, list.u.lis);
    }
}
#endif
