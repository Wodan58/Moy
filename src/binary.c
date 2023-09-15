/*
    module  : binary.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef BINARY_C
#define BINARY_C

/**
OK 2560  binary  :  DDDA	X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
void binary_(pEnv env)
{
    Node node, temp;

    PARM(3, DIP);
    code(env, unstack_);
    code(env, cons_);
    node = lst_pop(env->stck);

    lst_init(temp.u.lis);
    lst_copy(temp.u.lis, env->stck);
    (void)lst_pop(temp.u.lis);
    (void)lst_pop(temp.u.lis);
    temp.op = LIST_;
    lst_push(env->prog, temp);

    prog(env, node.u.lis);
}
#endif
