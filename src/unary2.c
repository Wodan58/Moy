/*
    module  : unary2.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef UNARY2_C
#define UNARY2_C

/**
OK 2520  unary2  :  DDDAA	X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void unary2_(pEnv env)
{ /*   Y  Z  [P]  unary2     ==>  Y'  Z'  */
    unsigned size;
    Node node, temp;

    PARM(3, DIP);
    node = vec_pop(env->stck);
    temp = vec_pop(env->stck);  /* Z */
    code(env, swap_);
    size = vec_size(env->prog); /* location of first Z, then Y' */
    vec_push(env->prog, temp);  /* first Z, then Y' */
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
    push(env, size);
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
}
#endif
