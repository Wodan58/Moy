/*
    module  : tailrec.c
    version : 1.7
    date    : 11/06/23
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
OK 2720  tailrec  :  DDDDA	[P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec_(pEnv env)
{
    unsigned size1, size2;
    Node first, second, third;

    PARM(3, IFTE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    size2 = pvec_cnt(env->prog);
    /*
	setup the continuation
    */
    code(env, tailrec_);
    prime(env, third);
    prime(env, second);
    prime(env, first);
    /*
	push the false branch of tailrec
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
	skip the false branch of tailrec
    */
    code(env, jump_);
    /*
	push the true branch of tailrec
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of tailrec
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0, 0);
    /*
	push the test of the tailrec
    */
    prog(env, first.u.lis);
}
#endif
