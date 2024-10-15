/*
    module  : infra.c
    version : 1.9
    date    : 09/26/24
*/
#ifndef INFRA_C
#define INFRA_C

/**
Q1  OK  2810  infra  :  DDA  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
void infra_(pEnv env)
{
    Node list, aggr;

    PARM(2, INFRA);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    /*
	the old stack is saved in the program
    */
    save(env, 0, 0, 0);
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
    vec_copy_all(env->stck, aggr.u.lis);
}
#endif
