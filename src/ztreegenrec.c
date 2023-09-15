/*
    module  : ztreegenrec.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef ZTREEGENREC_C
#define ZTREEGENREC_C

/**
OK 3150  (treegenrec)  :  DDDDU	T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void ztreegenrec_(pEnv env)
{
    unsigned size;
    Node list, node;

    PARM(1, DIP);
    list = lst_pop(env->stck);		/* item on top of the stack */
    node = lst_back(env->stck);		/* 2nd item on the stack */
    if (node.op == LIST_) {		/* list = [[O1] [O2] C] */
	prog(env, list.u.lis);	  /* C */
	(void)pop(env);
	(void)pop(env);

	code(env, cons_);
	code(env, cons_);

	node.u.lis = 0;
	node.op = LIST_;
	lst_push(env->prog, node);

	node.u.proc = ztreegenrec_;
	node.op = ANON_PRIME_;
	lst_push(env->prog, node);

	lst_push(env->prog, list);	/* list = [[O1] [O2] C] */

	size = lst_size(list.u.lis);	/* list = [[O1] [O2] C] */
	list = lst_at(list.u.lis, size - 2);	 /* list = [O2] */
	prog(env, list.u.lis);
    } else {				/* list = [[O1] [O2] C] */
	list = lst_back(list.u.lis);	/* list = [O1] */
	prog(env, list.u.lis);
    }
}
#endif
