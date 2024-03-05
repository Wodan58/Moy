/*
    module  : while.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef WHILE_C
#define WHILE_C

/**
Q2  OK  2700  while  :  DDP  [B] [D]  ->  ...
While executing B yields true executes D.
*/
void while_(pEnv env)
{
    int size;
    Node test, body;

    PARM(2, WHILE);
    env->stck = pvec_pop(env->stck, &body);
    env->stck = pvec_pop(env->stck, &test);
    size = pvec_cnt(env->prog);
    /*
	setup the continuation
    */
    code(env, while_);
    prime(env, body);
    prime(env, test);
    /*
	push the body of the while
    */
    prog(env, body.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size);
    /*
	jump on false past the body of the while
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, test.u.lis, 0, 0);
    /*
	push the test of the while
    */
    prog(env, test.u.lis);
}
#endif
