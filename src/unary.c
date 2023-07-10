/*
    module  : unary.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef UNARY_C
#define UNARY_C

/**
OK 2510  unary  :  DDA	X [P]  ->  R
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
    node = vec_pop(env->stck);
    /*
        restore the old stack after the program, except the former top
    */
    vec_init(temp.u.lis);
    vec_copy(temp.u.lis, env->stck);
    (void)vec_pop(temp.u.lis);
    temp.op = LIST_;
    vec_push(env->prog, temp);
    /*
        the list parameter is installed as the stack
    */
    prog(env, node.u.lis);
}
#endif
