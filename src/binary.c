/*
    module  : binary.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef BINARY_C
#define BINARY_C

/**
OK 2580  binary  :  DDDA	X Y [P]  ->  R
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
    node = vec_pop(env->stck);

    vec_init(temp.u.lis);
    vec_copy(temp.u.lis, env->stck);
    (void)vec_pop(temp.u.lis);
    (void)vec_pop(temp.u.lis);
    temp.op = LIST_;
    vec_push(env->prog, temp);

    prog(env, node.u.lis);
}
#endif
