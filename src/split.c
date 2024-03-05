/*
    module  : split.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef SPLIT_C
#define SPLIT_C

/**
Q1  OK  2840  split  :  DDAA  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void split_(pEnv env)
{
    int64_t i, j;
    unsigned size;
    Node aggr, list, node, temp;

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    /*
	register the location of the result aggregate
    */
    size = pvec_cnt(env->prog);
    /*
	build a result aggregate of the correct type
    */
    temp.op = aggr.op;
    switch (aggr.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	prime(env, temp);
	temp.u.lis = pvec_init();
	prime(env, temp);
	for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	    /*
		push the element to be split
	    */
	    node = pvec_nth(aggr.u.lis, i);
	    prime(env, node);
	    /*
		push the location of the result types
	    */
	    push(env, size);
	    /*
		add an instruction that builds the result types
	    */
	    code(env, tpush_);
	    /*
		save and restore the stack, if needed
	    */
	    save(env, list.u.lis, 1, 0);
	    /*
		push the program to be executed for each element
	    */
	    prog(env, list.u.lis);
	    /*
		push the element to be split
	    */
	    prime(env, node);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	temp.u.str[0] = 0;
	prime(env, temp);
	temp.u.str = GC_strdup(aggr.u.str);
	temp.u.str[0] = 0;
	prime(env, temp);
	node.op = CHAR_;
	for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
	    /*
		push the element that may be added to the result
	    */
	    node.u.num = aggr.u.str[i];
	    prime(env, node);
	    /*
		push the location of the result types
	    */
	    push(env, size);
	    /*
		add an instruction that builds the result types
	    */
	    code(env, tpush_);
	    /*
		save and restore the stack, if needed
	    */
	    save(env, list.u.lis, 1, 0);
	    /*
		push the program to be executed for each element
	    */
	    prog(env, list.u.lis);
	    /*
		push the element that may be added to the result
	    */
	    prime(env, node);
	}
	break;

    case SET_:
	temp.u.set = 0;
	prime(env, temp);
	prime(env, temp);
	node.op = INTEGER_;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element that may be added to the result
		*/
		node.u.num = i;
		prime(env, node);
		/*
		    push the location of the result types
		*/
		push(env, size);
		/*
		    add an instruction that builds the result types
		*/
		code(env, tpush_);
		/*
		    save and restore the stack, if needed
		*/
		save(env, list.u.lis, 1, 0);
		/*
		    push the program to be executed for each element
		*/
		prog(env, list.u.lis);
		/*
		    push the element that may be added to the result
		*/
		prime(env, node);
	    }
	break;
    }
}
#endif
