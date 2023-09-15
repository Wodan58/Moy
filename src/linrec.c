/*
    module  : linrec.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef LINREC_C
#define LINREC_C

/**
OK 2710  linrec  :  DDDDU	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void linrec_(pEnv env)
{
    unsigned size1, size2;
    Node first, second, third, fourth;

    PARM(4, LINREC);
    fourth = lst_pop(env->stck);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    /*
	register the return address
    */
    size2 = lst_size(env->prog);
    /*
	execute R2 after returning from the recursion
    */
    prog(env, fourth.u.lis);
    /*
	setup the continuation
    */
    code(env, linrec_);
    lst_push(env->prog, fourth);
    lst_push(env->prog, third);
    lst_push(env->prog, second);
    lst_push(env->prog, first);
    /*
	push the R1 branch of linrec
    */
    prog(env, third.u.lis);
    /*
	register the target location for the false branch
    */
    size1 = lst_size(env->prog);
    /*
	push the jump address onto the program stack
    */
    push(env, size2);
    /*
	skip the false branch of linrec
    */
    code(env, jump_);
    /*
	push the true branch of linrec
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of linrec
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0);
    /*
	push the test of linrec
    */
    prog(env, first.u.lis);
}
#endif
