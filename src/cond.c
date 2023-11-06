/*
    module  : cond.c
    version : 1.7
    date    : 11/06/23
*/
#ifndef COND_C
#define COND_C

/**
OK 2690  cond  :  DDA	[..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
void cond_(pEnv env)
{
    int i, j;
    unsigned size1, size2;
    Node aggr, elem, node;

    PARM(1, CASE);
    env->stck = pvec_pop(env->stck, &aggr);
    /*
	jump address past last cond line
    */
    size2 = pvec_cnt(env->prog);
    /*
	the last cond line comes without test and no jump is needed
    */
    elem = pvec_nth(aggr.u.lis, 0);
    prog(env, elem.u.lis);
    for (i = 1, j = pvec_cnt(aggr.u.lis); i < j; i++) {
	/*
	    jump address to the next cond line
	*/
	size1 = pvec_cnt(env->prog);
	/*
	    read a cond line
	*/
	elem = pvec_nth(aggr.u.lis, i);
	/*
	    push the jump address onto the program stack
	*/
	push(env, size2);
	/*
	    jump after executing the rest of the cond line
	*/
	code(env, jump_);
	/*
	    push the rest of the cond line
	*/
	prog(env, elem.u.lis);
	node = pop(env);
	/*
	    push the jump address onto the program stack
	*/
	push(env, size1);
	/*
	    jump on false to the next cond line; remove condition code
	*/
	code(env, pfalse_);
	/*
	    save the stack before the condition and restore it afterwards with
	    the condition code included.
	*/
	save(env, node.u.lis, 0, 0);
	/*
	    push the test of the cond line
	*/
	prog(env, node.u.lis);
    }
}
#endif
