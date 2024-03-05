/*
    module  : genrecaux.c
    version : 1.12
    date    : 03/05/24
*/
#ifndef GENRECAUX_C
#define GENRECAUX_C

/**
Q1  OK  3290  #genrec  :  DDDDDA  [[B] [T] [R1] R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void genrecaux_(pEnv env)
{
    int i, j, size;
    unsigned size1, size2;
    Node first, second, third, aggr, node;

    PARM(1, DIP);
    env->stck = pvec_pop(env->stck, &aggr);	/* item on top of the stack */
    first = pvec_lst(aggr.u.lis);
    size = pvec_cnt(aggr.u.lis);
    second = pvec_nth(aggr.u.lis, size - 2);
    third = pvec_nth(aggr.u.lis, size - 3);
    /*
	record the jump location after the false branch
    */
    size2 = pvec_cnt(env->prog);
    /*
	push R2, excluding [B], [T], [R1]
    */
    for (i = 0, j = pvec_cnt(aggr.u.lis) - 3; i < j; i++)
	env->prog = pvec_add(env->prog, pvec_nth(aggr.u.lis, i));

    code(env, cons_);		/* build [[[B] [T] [R1] R2] genrecaux_] */
    code(env, cons_);		/* build [genrecaux_] */

    node.u.lis = 0;
    node.op = LIST_;
    prime(env, node);

    node.u.proc = genrecaux_;
    node.op = ANON_PRIME_;
    prime(env, node);
    /*
	push the item that was on top of the stack
    */
    prime(env, aggr);
    /*
	push R1
    */
    prog(env, third.u.lis);
    /*
	record the jump location before the false branch
    */
    size1 = pvec_cnt(env->prog);
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
    save(env, first.u.lis, 0, 0);
    /*
	push the test of genrec
    */
    prog(env, first.u.lis);
}
#endif
