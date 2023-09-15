/*
    module  : infra.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef INFRA_C
#define INFRA_C

/**
OK 2810  infra  :  DDA	L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
void infra_(pEnv env)
{
    Node aggr, list, node;

    PARM(2, INFRA);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    /*
	the old stack is restored with the list on top
    */
    code(env, unstack_);
    /*
	the list becomes the top of the stack
    */
    code(env, cons_);
    /*
	the old stack is saved in the program
    */
    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);
    node.op = LIST_;
    lst_push(env->prog, node);
    /*
	after executing the program the stack is listed
    */
    code(env, stack_);
    /*
	the program is executed on the alternate stack
    */
    prog(env, list.u.lis);
    /*
	the list parameter is installed as the stack
    */
    lst_copy(env->stck, aggr.u.lis);
}
#endif
