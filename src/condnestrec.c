/*
    module  : condnestrec.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef CONDNESTREC_C
#define CONDNESTREC_C

/**
OK 2750  condnestrec  :  DU	[ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
void condnestrec_(pEnv env)
{
    unsigned size, size2;
    int i, j, k, l, limit;
    Node aggr, elem, node;

    PARM(1, CASE);
    aggr = lst_pop(env->stck);
    size2 = lst_size(env->prog);
    for (k = 0, l = lst_size(aggr.u.lis); k < l; k++) {
	/*
	    jump address of the next cond line, or the end of it
	*/
	size = lst_size(env->prog);
	/*
	    push the jump address onto the program stack
	*/
	push(env, size2);
	/*
	    jump on true to the end of the program
	*/
	code(env, jump_);
	/*
	    read a cond line
	*/
	elem = lst_at(aggr.u.lis, k);
	limit = k ? 2 : 1;
	for (i = 0, j = lst_size(elem.u.lis) - limit; i < j; i++) {
	    node = lst_at(elem.u.lis, i);
	    prog(env, node.u.lis);
	    /*
		push the continuation
	    */
	    code(env, condnestrec_);
	    node.u.lis = aggr.u.lis;
	    node.op = LIST_;
	    lst_push(env->prog, node);
	}
	node = lst_at(elem.u.lis, i);
	prog(env, node.u.lis);
	if (k) {
	    /*
		push the jump address onto the program stack
	    */
	    push(env, size);
	    /*
		jump on false to the next cond line; remove condition code
	    */
	    code(env, pfalse_);
	    node = lst_back(elem.u.lis);
	    save(env, node.u.lis, 0);
	    /*
		push the condition of the cond line
	    */
	    prog(env, node.u.lis);
	}
    }
}
#endif
