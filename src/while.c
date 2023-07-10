/*
    module  : while.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef WHILE_C
#define WHILE_C

/**
OK 2720  while  :  DDU	[B] [D]  ->  ...
While executing B yields true executes D.
*/
void while_(pEnv env)
{
    int size;
    Node test, body;

    PARM(2, WHILE);
    body = vec_pop(env->stck);
    test = vec_pop(env->stck);
    size = vec_size(env->prog);
    /*
        setup the continuation
    */
    code(env, while_);
    vec_push(env->prog, body);
    vec_push(env->prog, test);
    /*
        push the body of the while
    */
    prog(env, body.u.lis);
    /*
        push the jump address onto the program stack
    */
    push(env, size);
    /*
        jump on false past the body of the while
    */
    code(env, fjump_);
    /*
        save the stack before the condition and restore it afterwards with
        the condition code included.
    */
    save(env, test.u.lis, 0);
    /*
        push the test of the while
    */
    prog(env, test.u.lis);
}
#endif
