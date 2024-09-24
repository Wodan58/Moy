/*
    module  : tailrec.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
Q3  OK  2720  tailrec  :  DDDDA  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec_(pEnv env)
{
    unsigned size1, size2;
    Node first, second, third;

    PARM(3, IFTE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    size2 = vec_size(env->prog);
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
    size1 = vec_size(env->prog);
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
