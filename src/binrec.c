/*
    module  : binrec.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef BINREC_C
#define BINREC_C

/**
OK 2730  binrec  :  DDDDU	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void binrec_(pEnv env)
{
    unsigned size1, size2, size3;
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
    code(env, binrec_);
    lst_push(env->prog, fourth);
    lst_push(env->prog, third);
    lst_push(env->prog, second);
    lst_push(env->prog, first);
    /*
	save point for the first result
    */
    size3 = lst_size(env->prog);
    code(env, id_);
    /*
	setup the continuation
    */
    code(env, binrec_);
    lst_push(env->prog, fourth);
    lst_push(env->prog, third);
    lst_push(env->prog, second);
    lst_push(env->prog, first);
    /*
	pop the result and save it in the program
    */
    push(env, size3);
    /*
	update the result
    */
    code(env, cpush_);
    /*
	push the R1 branch of binrec
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
	skip the false branch of binrec
    */
    code(env, jump_);
    /*
	push the true branch of binrec
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of binrec
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0);
    /*
	push the test of binrec
    */
    prog(env, first.u.lis);
}
#endif
