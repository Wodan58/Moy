/*
    module  : ternary.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef TERNARY_C
#define TERNARY_C

/**
OK 2570  ternary  :  DDDDA 	X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
void ternary_(pEnv env)
{
    Node list;

    PARM(4, DIP);
    /*
	read the program from the stack
    */
    env->stck = pvec_pop(env->stck, &list);
    /*
	the old stack is saved without the former top and restored with the new
	top.
    */
    save(env, 0, 0, 3);
    /*
	the program on top of the stack is executed
    */
    prog(env, list.u.lis);
}
#endif
