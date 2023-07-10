/*
    module  : _treerec.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef _TREEREC_C
#define _TREEREC_C

/**
OK 3190  (_treerec)  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void _treerec_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    list = vec_pop(env->stck);		/* item on top of the stack */
    node = vec_back(env->stck);		/* 2nd item on the stack */
    if (node.op == LIST_) {		/* list = [[O] C] */

        prog(env, list.u.lis);          /* C */
        (void)pop(env);

        code(env, cons_);
        code(env, cons_);

        node.u.lis = 0;
        node.op = LIST_;
        vec_push(env->prog, node);

        node.u.proc = _treerec_;
        node.op = ANON_PRIME_;
        vec_push(env->prog, node);

        vec_push(env->prog, list);	/* list = [[O] C] */
    } else {
        list = vec_back(list.u.lis);	/* list = [O] */
        prog(env, list.u.lis);
    }
}
#endif
