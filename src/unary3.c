/*
    module  : unary3.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef UNARY3_C
#define UNARY3_C

/**
OK 2530  unary3  :  DDDDAAA	X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
PRIVATE void unary3_(pEnv env)
{ /*  X Y Z [P]  unary3    ==>  X' Y' Z'        */
    unsigned size1, size2;
    Node param1, param2, node;

    PARM(4, DIP);
    node = vec_pop(env->stck);
    param2 = vec_pop(env->stck);
    param1 = vec_pop(env->stck);

    code(env, rolldown_);

    size2 = vec_size(env->prog); /* location of first Z, then Y' */
    vec_push(env->prog, param2); /* first Z, then Y' */

    size1 = vec_size(env->prog); /* location of first Y, then X' */
    vec_push(env->prog, param1); /* first Y, then X' */

    /*
        save the stack before the condition and restore it afterwards with
        the condition code included.
    */
    undo(env, node.u.lis, 1);
    /*
        Calculate Z' on top of the stack
    */
    prog(env, node.u.lis);
    /*
        Push the address of Z
    */
    push(env, size2);
    /*
        Swap Z and Y'
    */
    code(env, cswap_);
    /*
        save the stack before the condition and restore it afterwards with
        the condition code included.
    */
    undo(env, node.u.lis, 1);
    /*
        Calculate Y' on top of the stack
    */
    prog(env, node.u.lis);
    /*
        Push the address of Y
    */
    push(env, size1);
    /*
        Swap Y and X'
    */
    code(env, cswap_);
    /*
        save the stack before the condition and restore it afterwards with
        the condition code included.
    */
    undo(env, node.u.lis, 1);
    /*
        Calculate X' on top of the stack
    */
    prog(env, node.u.lis);
}
#endif
