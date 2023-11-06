/*
    module  : linrec.c
    version : 1.7
    date    : 11/06/23
*/
#ifndef LINREC_C
#define LINREC_C

/**
OK 2710  linrec  :  DDDDDA	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void linrec_(pEnv env)
{
    unsigned size1, size2;
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
    code(env, linrec_);
    prime(env, fourth);
    prime(env, third);
    prime(env, second);
    prime(env, first);
    /*
	push the R1 branch of linrec
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
	skip the false branch of linrec
    */
    code(env, jump_);
    /*
	push the true branch of linrec
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of linrec
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0, 0);
    /*
	push the test of linrec
    */
    prog(env, first.u.lis);
}
#endif
