/*
    module  : ternary.c
    version : 1.5
    date    : 09/15/23
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
    Node list, temp;

    PARM(4, DIP);
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
    lst_init(temp.u.lis);
    lst_copy(temp.u.lis, env->stck);
    (void)lst_pop(temp.u.lis);
    (void)lst_pop(temp.u.lis);
    (void)lst_pop(temp.u.lis);
    temp.op = LIST_;
    lst_push(env->prog, temp);
    /*
	execute program
    */
    prog(env, list.u.lis);
}
#endif
