/*
    module  : _treegenrec.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef _TREEGENREC_C
#define _TREEGENREC_C

/**
OK 3180  (_treegenrec)  :  DDDDU	T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void _treegenrec_(pEnv env)
{
    unsigned size;
    Node list, node;

    PARM(1, DIP);
    list = vec_pop(env->stck);		/* item on top of the stack */
    node = vec_back(env->stck);		/* 2nd item on the stack */
    if (node.op == LIST_) {		/* list = [[O1] [O2] C] */
        prog(env, list.u.lis);          /* C */
        (void)pop(env);
        (void)pop(env);

        code(env, cons_);
        code(env, cons_);

        node.u.lis = 0;
        node.op = LIST_;
        vec_push(env->prog, node);

        node.u.proc = _treegenrec_;
        node.op = ANON_PRIME_;
        vec_push(env->prog, node);

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
