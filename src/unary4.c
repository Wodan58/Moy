/*
    module  : unary4.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef UNARY4_C
#define UNARY4_C

/**
OK 2520  unary4  :  DDDDDAAAA	X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
PRIVATE void unary4_(pEnv env)
{	/*  X Y Z W [P]  unary4    ==>  X' Y' Z' W'	*/
    unsigned size1, size2, size3;
    Node param1, param2, param3, list;

    PARM(5, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &param3);
    env->stck = pvec_pop(env->stck, &param2);
    env->stck = pvec_pop(env->stck, &param1);

    code(env, swap_);
    code(env, rolldownd_);

    size3 = pvec_cnt(env->prog);	/* location of first W, then Z' */
    prime(env, param3);			/* first W, then Z' */

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
	Calculate W' on top of the stack
    */
    prog(env, list.u.lis);
    /*
	Push the address of W
    */
    push(env, size3);
    /*
	Swap W and Z'
    */
    code(env, cswap_);
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
