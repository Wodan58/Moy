/*
    module  : all.c
    version : 1.8
    date    : 09/19/23
*/
#ifndef ALL_C
#define ALL_C

/**
OK 2860  all  :  DDA	A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void all_(pEnv env)
{
    int64_t i, j;
    unsigned size;
    Node aggr, list, node;

    PARM(2, STEP);
    size = lst_size(env->prog);
    /*
	if all tests pass, the result will be true.
    */
    code(env, true_);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = 0, j = lst_size(aggr.u.lis); i < j; i++) {
	    /*
		push the location of the result type
	    */
	    push(env, size);
	    /*
		add an instruction that builds the result type
	    */
	    code(env, jfalse_);
	    /*
		save and restore the stack, if needed
	    */
	    save(env, list.u.lis, 1);
	    /*
		push the program to be executed for each element
	    */
	    prog(env, list.u.lis);
	    /*
		push the element to be mapped
	    */
	    node = lst_at(aggr.u.lis, i);
	    prime(env, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
	    /*
		push the location of the result type
	    */
	    push(env, size);
	    /*
		add an instruction that builds the result type
	    */
	    code(env, jfalse_);
	    /*
		save and restore the stack, if needed
	    */
	    save(env, list.u.lis, 1);
	    /*
		push the program to be executed for each element
	    */
	    prog(env, list.u.lis);
	    /*
		push the element to be mapped
	    */
	    node.u.num = aggr.u.str[i];
	    lst_push(env->prog, node);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the location of the result type
		*/
		push(env, size);
		/*
		    add an instruction that builds the result type
		*/
		code(env, jfalse_);
		/*
		    save and restore the stack, if needed
		*/
		save(env, list.u.lis, 1);
		/*
		    push the program to be executed for each element
		*/
		prog(env, list.u.lis);
		/*
		    push the element to be mapped
		*/
		node.u.num = i;
		lst_push(env->prog, node);
	    }
	break;

    default:
	break;
    }
}
#endif
