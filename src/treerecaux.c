/*
    module  : treerecaux.c
    version : 1.14
    date    : 09/17/24
*/
#ifndef TREERECAUX_C
#define TREERECAUX_C

/**
Q1  OK  3310  #treerec  :  DDDDA  T [[O] C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerecaux_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    list = vec_pop(env->stck);		/* item on top of the stack */
    node = vec_back(env->stck);		/* 2nd item on the stack */
    if (node.op == LIST_) {		/* list = [[O] C] */

	prog(env, list.u.lis);		/* C */
	(void)pop(env);

	code(env, cons_);
	code(env, cons_);

	vec_init(node.u.lis);
	prime(env, node);

	node.u.proc = treerecaux_;
	node.op = ANON_PRIME_;
	prime(env, node);

	prime(env, list);		/* list = [[O] C] */
    } else {
	list = vec_back(list.u.lis);	/* list = [O] */
	prog(env, list.u.lis);
    }
}
#endif
