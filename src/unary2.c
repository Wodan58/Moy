/*
    module  : unary2.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef UNARY2_C
#define UNARY2_C

/**
OK 2500  unary2  :  DDDAA	X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void unary2_(pEnv env)
{	/*   Y  Z  [P]  unary2     ==>  Y'  Z'  */
    unsigned size;
    Node list, node;

    PARM(3, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node);	/* Z */
    code(env, swap_);
    size = pvec_cnt(env->prog); /* location of first Z, then Y' */
    prime(env, node);		/* first Z, then Y' */
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
    push(env, size);
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
}
#endif
