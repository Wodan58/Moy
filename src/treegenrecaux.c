/*
    module  : treegenrecaux.c
    version : 1.15
    date    : 11/20/24
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
    list = vec_pop(env->stck);		/* item on top of the stack */
    node = vec_back(env->stck);		/* 2nd item on the stack */
    if (node.op == LIST_) {		/* list = [[O1] [O2] C] */
	prog(env, list.u.lis);		/* C */
	vec_reduce(env->prog, 2);

	code(env, cons_);
	code(env, cons_);

	vec_init(node.u.lis);
	prime(env, node);

	node.u.proc = treegenrecaux_;
	node.op = ANON_PRIME_;
	prime(env, node);

	vec_push(env->prog, list);	/* list = [[O1] [O2] C] */

	size = vec_size(list.u.lis);	/* list = [[O1] [O2] C] */
	list = vec_at(list.u.lis, size - 2);	/* list = [O2] */
	prog(env, list.u.lis);
    } else {				/* list = [[O1] [O2] C] */
	list = vec_back(list.u.lis);	/* list = [O1] */
	prog(env, list.u.lis);
    }
}
#endif
