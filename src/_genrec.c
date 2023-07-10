/*
    module  : _genrec.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef _GENREC_C
#define _GENREC_C

/**
OK 3170  (_genrec)  :  DDDDU	[B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void _genrec_(pEnv env)
{
    int i, j, size;
    unsigned size1, size2;
    Node first, second, third, aggr, node;

    PARM(1, DIP);
    aggr = vec_pop(env->stck); /* item on top of the stack */
    first = vec_back(aggr.u.lis);
    size = vec_size(aggr.u.lis);
    second = vec_at(aggr.u.lis, size - 2);
    third = vec_at(aggr.u.lis, size - 3);
    /*
        record the jump location after the false branch
    */
    size2 = vec_size(env->prog);
    /*
        push R2, excluding [B], [T], [R1]
    */
    for (i = 0, j = vec_size(aggr.u.lis) - 3; i < j; i++)
        vec_push(env->prog, vec_at(aggr.u.lis, i));

    code(env, cons_);
    code(env, cons_);

    node.u.lis = 0;
    node.op = LIST_;
    vec_push(env->prog, node);

    node.u.proc = _genrec_;
    node.op = ANON_PRIME_;
    vec_push(env->prog, node);

    node.u.lis = aggr.u.lis;
    node.op = LIST_;
    vec_push(env->prog, node);
    /*
        push R1
    */
    prog(env, third.u.lis);
    /*
        record the jump location before the false branch
    */
    size1 = vec_size(env->prog);
    /*
        push the jump address onto the program stack
    */
    push(env, size2);
    /*
        jump after the false branch of genrec
    */
    code(env, jump_);
    /*
        push the true branch of genrec
    */
    prog(env, second.u.lis);
    /*
        push the jump address onto the program stack
    */
    push(env, size1);
    /*
        jump on false before the false branch
    */
    code(env, fjump_);
    /*
        save the stack before the condition and restore it afterwards with
        the condition code included.
    */
    save(env, first.u.lis, 0);
    /*
        push the test of genrec
    */
    prog(env, first.u.lis);
}
#endif
