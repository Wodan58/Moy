/*
    module  : tailrec.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
OK 2720  tailrec  :  DDDU	[P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec_(pEnv env)
{
    unsigned size1, size2;
    Node first, second, third;

    PARM(3, IFTE);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    size2 = lst_size(env->prog);
    /*
	setup the continuation
    */
    code(env, tailrec_);
    lst_push(env->prog, third);
    lst_push(env->prog, second);
    lst_push(env->prog, first);
    /*
	push the false branch of tailrec
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
	skip the false branch of tailrec
    */
    code(env, jump_);
    /*
	push the true branch of tailrec
    */
    prog(env, second.u.lis);
    /*
	push the jump address onto the program stack
    */
    push(env, size1);
    /*
	jump on false past the true branch of tailrec
    */
    code(env, fjump_);
    /*
	save the stack before the condition and restore it afterwards with
	the condition code included.
    */
    save(env, first.u.lis, 0);
    /*
	push the test of the tailrec
    */
    prog(env, first.u.lis);
}
#endif
