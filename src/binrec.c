/*
    module  : binrec.c
    version : 1.7
    date    : 11/06/23
*/
#ifndef BINREC_C
#define BINREC_C

/**
OK 2730  binrec  :  DDDDDA	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void binrec_(pEnv env)
{
    unsigned size1, size2, size3;
    Node first, second, third, fourth;

    PARM(4, LINREC);
    env->stck = pvec_pop(env->stck, &fourth);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    /*
	register the return address
    */
    size2 = pvec_cnt(env->prog);
    /*
	execute R2 after returning from the recursion
    */
    prog(env, fourth.u.lis);
    /*
	setup the continuation
    */
    code(env, binrec_);
    prime(env, fourth);
    prime(env, third);
    prime(env, second);
    prime(env, first);
    /*
	save point for the first result
    */
    size3 = pvec_cnt(env->prog);
    code(env, id_);
    /*
	setup the continuation
    */
    code(env, binrec_);
    prime(env, fourth);
    prime(env, third);
    prime(env, second);
    prime(env, first);
    /*
	pop the result and save it in the program
    */
    push(env, size3);
    /*
	update the result
    */
    code(env, cpush_);
    /*
	push the R1 branch of binrec
    */
    prog(env, third.u.lis);
    /*
	register the target location for the false branch
    */
    size1 = pvec_cnt(env->prog);
    /*
	push the jump address onto the program stack
    */
    push(env, size2);
    /*
	skip the false branch of binrec
    */
    code(env, jump_);
    /*
	push the true branch of binrec
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of binrec
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0, 0);
    /*
	push the test of binrec
    */
    prog(env, first.u.lis);
}
#endif
