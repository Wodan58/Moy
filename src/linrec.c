/*
    module  : linrec.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef LINREC_C
#define LINREC_C

/**
Q4  OK  2710  linrec  :  DDDDDA  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void linrec_(pEnv env)
{
    unsigned size1, size2;
    Node first, second, third, fourth;

    PARM(4, LINREC);
    fourth = vec_pop(env->stck);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    /*
	register the return address
    */
    size2 = vec_size(env->prog);
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
    size1 = vec_size(env->prog);
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
