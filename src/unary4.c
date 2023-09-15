/*
    module  : unary4.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef UNARY4_C
#define UNARY4_C

/**
OK 2520  unary4  :  DDDDDAAAA	X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
PRIVATE void unary4_(pEnv env)
{	/*  X Y Z W [P]  unary4    ==>  X' Y' Z' W'	*/
    unsigned size1, size2, size3;
    Node param1, param2, param3, node;

    PARM(5, DIP);
    node = lst_pop(env->stck);
    param3 = lst_pop(env->stck);
    param2 = lst_pop(env->stck);
    param1 = lst_pop(env->stck);

    code(env, swap_);
    code(env, rolldownd_);

    size3 = lst_size(env->prog); /* location of first W, then Z' */
    lst_push(env->prog, param3); /* first W, then Z' */

    size2 = lst_size(env->prog); /* location of first Z, then Y' */
    lst_push(env->prog, param2); /* first Z, then Y' */

    size1 = lst_size(env->prog); /* location of first Y, then X' */
    lst_push(env->prog, param1); /* first Y, then X' */

    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    undo(env, node.u.lis, 1);
    /*
	Calculate W' on top of the stack
    */
    prog(env, node.u.lis);
    /*
	Push the address of W
    */
    push(env, size3);
    /*
	Swap W and Z'
    */
    code(env, cswap_);
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
