/*
    module  : unary3.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef UNARY3_C
#define UNARY3_C

/**
OK 2510  unary3  :  DDDDAAA	X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
PRIVATE void unary3_(pEnv env)
{	/*  X Y Z [P]  unary3    ==>  X' Y' Z'	*/
    unsigned size1, size2;
    Node param1, param2, list;

    PARM(4, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &param2);
    env->stck = pvec_pop(env->stck, &param1);

    code(env, rolldown_);

    size2 = pvec_cnt(env->prog);	/* location of first Z, then Y' */
    prime(env, param2);			/* first Z, then Y' */

    size1 = pvec_cnt(env->prog);	/* location of first Y, then X' */
    prime(env, param1);			/* first Y, then X' */

    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, list.u.lis, 1, 1);
    /*
	Calculate Z' on top of the stack
    */
    prog(env, list.u.lis);
    /*
	Push the address of Z
    */
    push(env, size2);
    /*
	Swap Z and Y'
    */
    code(env, cswap_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, list.u.lis, 1, 1);
    /*
	Calculate Y' on top of the stack
    */
    prog(env, list.u.lis);
    /*
	Push the address of Y
    */
    push(env, size1);
    /*
	Swap Y and X'
    */
    code(env, cswap_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, list.u.lis, 1, 1);
    /*
	Calculate X' on top of the stack
    */
    prog(env, list.u.lis);
}
#endif
