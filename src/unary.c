/*
    module  : unary.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef UNARY_C
#define UNARY_C

/**
OK 2490  unary  :  DDA	X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
void unary_(pEnv env)
{
    Node node, temp;

    PARM(2, DIP);
    /*
	restore the old stack
    */
    code(env, unstack_);
    /*
	include the result of the program in the old stack
    */
    code(env, cons_);
    /*
	remove the program from the stack
    */
    node = lst_pop(env->stck);
    /*
	restore the old stack after the program, except the former top
    */
    lst_init(temp.u.lis);
    lst_copy(temp.u.lis, env->stck);
    (void)lst_pop(temp.u.lis);
    temp.op = LIST_;
    lst_push(env->prog, temp);
    /*
	the list parameter is installed as the stack
    */
    prog(env, node.u.lis);
}
#endif
