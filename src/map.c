/*
    module  : map.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef MAP_C
#define MAP_C

/**
OK 2790  map  :  DDA	A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void map_(pEnv env)
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
	for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	    /*
		push the location of the result type
	    */
	    push(env, size);
	    /*
		add an instruction that builds the result type
	    */
	    code(env, push_);
	    /*
		save and restore the stack, if needed
	    */
	    save(env, list.u.lis, 1, 0);
	    /*
		push the program to be executed for each element
	    */
	    prog(env, list.u.lis);
	    /*
		push the element to be mapped
	    */
	    prime(env, pvec_nth(aggr.u.lis, i));
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	temp.u.str = GC_strdup(aggr.u.str);
	temp.u.str[0] = 0;
	prime(env, temp);
	node.op = CHAR_;
	for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
	    /*
		push the location of the result type
	    */
	    push(env, size);
	    /*
		add an instruction that builds the result type
	    */
	    code(env, push_);
	    /*
		save and restore the stack, if needed
	    */
	    save(env, list.u.lis, 1, 0);
	    /*
		push the program to be executed for each element
	    */
	    prog(env, list.u.lis);
	    /*
		push the element to be mapped
	    */
	    node.u.num = aggr.u.str[i];
	    prime(env, node);
	}
	break;

    case SET_:
	temp.u.set = 0;
	prime(env, temp);
	node.op = INTEGER_;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the location of the result type
		*/
		push(env, size);
		/*
		    add an instruction that builds the result type
		*/
		code(env, push_);
		/*
		    save and restore the stack, if needed
		*/
		save(env, list.u.lis, 1, 0);
		/*
		    push the program to be executed for each element
		*/
		prog(env, list.u.lis);
		/*
		    push the element to be mapped
		*/
		node.u.num = i;
		prime(env, node);
	    }
	break;

    default:
	break;
    }
}
#endif
