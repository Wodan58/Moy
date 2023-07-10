/*
    module  : ternary.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TERNARY_C
#define TERNARY_C

/**
OK 2590  ternary  :  DDDDA 	X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
void ternary_(pEnv env)
{
    Node list, temp;

    PARM(4, DIP);
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
    vec_init(temp.u.lis);
    vec_copy(temp.u.lis, env->stck);
    (void)vec_pop(temp.u.lis);
    (void)vec_pop(temp.u.lis);
    (void)vec_pop(temp.u.lis);
    temp.op = LIST_;
    vec_push(env->prog, temp);
    /*
        execute program
    */
    prog(env, list.u.lis);
}
#endif
