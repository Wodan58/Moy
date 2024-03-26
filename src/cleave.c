/*
    module  : cleave.c
    version : 1.8
    date    : 03/21/24
*/
#ifndef CLEAVE_C
#define CLEAVE_C

/**
Q2  OK  2580  cleave  :  DDDAA  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
void cleave_(pEnv env)
{	/*	X [P1] [P2]  cleave  ==>  X1 X2	*/
    unsigned size;
    Node first, second;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    /*
	swap X1 and X2
    */
    code(env, swap_);
    /*
	push the location of X1 onto the code stack
    */
    size = pvec_cnt(env->prog);
    /*
	push X1 that was saved at this location in the code
    */
    code(env, id_);
    /*
	push the second program, producing X2
    */
    prog(env, second.u.lis);
    /*
	Push the address of X1
    */
    push(env, size);
    /*
	Pop X1 and write it at the given address
    */
    code(env, cpush_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0, 0);
    /*
	push the first program, producing X1
    */
    prog(env, first.u.lis);
}
#endif
