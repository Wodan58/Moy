/*
    module  : zgenrec.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef ZGENREC_C
#define ZGENREC_C

/**
OK 3140  (genrec)  :  DDDDU	[B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void zgenrec_(pEnv env)
{
    int i, j, size;
    unsigned size1, size2;
    Node first, second, third, aggr, node;

    PARM(1, DIP);
    aggr = lst_pop(env->stck); /* item on top of the stack */
    first = lst_back(aggr.u.lis);
    size = lst_size(aggr.u.lis);
    second = lst_at(aggr.u.lis, size - 2);
    third = lst_at(aggr.u.lis, size - 3);
    /*
	record the jump location after the false branch
    */
    size2 = lst_size(env->prog);
    /*
	push R2, excluding [B], [T], [R1]
    */
    for (i = 0, j = lst_size(aggr.u.lis) - 3; i < j; i++)
	lst_push(env->prog, lst_at(aggr.u.lis, i));

    code(env, cons_);
    code(env, cons_);

    node.u.lis = 0;
    node.op = LIST_;
    lst_push(env->prog, node);

    node.u.proc = zgenrec_;
    node.op = ANON_PRIME_;
    lst_push(env->prog, node);

    node.u.lis = aggr.u.lis;
    node.op = LIST_;
    lst_push(env->prog, node);
    /*
	push R1
    */
    prog(env, third.u.lis);
    /*
	record the jump location before the false branch
    */
    size1 = lst_size(env->prog);
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
