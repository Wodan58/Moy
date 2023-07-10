/*
    module  : nullary.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef NULLARY_C
#define NULLARY_C

/**
OK 2500  nullary  :  DA	[P]  ->  R
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
    list = vec_pop(env->stck);
    /*
        restore the old stack after the test
    */
    vec_init(node.u.lis);
    vec_copy(node.u.lis, env->stck);
    node.op = LIST_;
    vec_push(env->prog, node);
    /*
        execute program
    */
    prog(env, list.u.lis);
}
#endif
