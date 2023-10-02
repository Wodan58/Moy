/*
    module  : ifte.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef IFTE_C
#define IFTE_C

/**
OK 2600  ifte  :  DDDP	[B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
void ifte_(pEnv env)
{
    unsigned size1, size2;
    Node first, second, third;

    PARM(3, IFTE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    /*
	record the jump location after the false branch
    */
    size2 = pvec_cnt(env->prog);
    /*
	push the false branch of the ifte
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
	jump past the false branch of ifte
    */
    code(env, jump_);
    /*
	push the true branch of the ifte
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of ifte
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0, 0);
    /*
	push the test of the ifte
    */
    prog(env, first.u.lis);
}
#endif
