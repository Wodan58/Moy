/*
    module  : ternary.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef TERNARY_C
#define TERNARY_C

/**
Q1  OK  2570  ternary  :  DDDDA  X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
void ternary_(pEnv env)
{
    Node node;

    PARM(4, DIP);
    /*
	read the program from the stack
    */
    node = vec_pop(env->stck);
    /*
	the old stack is saved without the former top and restored with the new
	top.
    */
    save(env, 0, 0, 3);
    /*
	the program on top of the stack is executed
    */
    prog(env, node.u.lis);
}
#endif
