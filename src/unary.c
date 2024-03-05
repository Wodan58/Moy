/*
    module  : unary.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef UNARY_C
#define UNARY_C

/**
Q1  OK  2490  unary  :  DDA  X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
void unary_(pEnv env)
{
    Node list;

    PARM(2, DIP);
    /*
	remove the program from the stack
    */
    env->stck = pvec_pop(env->stck, &list);
    /*
	the old stack is saved without the former top and restored with the new
	top.
    */
    save(env, 0, 0, 1);
    /*
	the program on top of the stack is executed
    */
    prog(env, list.u.lis);
}
#endif
