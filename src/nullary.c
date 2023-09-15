/*
    module  : nullary.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef NULLARY_C
#define NULLARY_C

/**
OK 2480  nullary  :  DA	[P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
void nullary_(pEnv env)
{
    Node list, node;

    PARM(1, DIP);
    /*
	replace the new stack with the old stack
    */
    code(env, unstack_);
    /*
	include the test result in the old stack
    */
    code(env, cons_);
    /*
	read the program from the stack
    */
    list = lst_pop(env->stck);
    /*
	restore the old stack after the test
    */
    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);
    node.op = LIST_;
    lst_push(env->prog, node);
    /*
	execute program
    */
    prog(env, list.u.lis);
}
#endif
