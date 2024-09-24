/*
    module  : binary.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef BINARY_C
#define BINARY_C

/**
Q1  OK  2560  binary  :  DDDA  X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
void binary_(pEnv env)
{
    Node node;

    PARM(3, DIP);
    node = vec_pop(env->stck);
    /*
	the old stack is saved without the former top and restored with the new
	top.
    */
    save(env, 0, 0, 2);
    /*
	the program on top of the stack is executed
    */
    prog(env, node.u.lis);
}
#endif
