/*
    module  : fpush.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef FPUSH_C
#define FPUSH_C

/**
OK 3380  (fpush)  :  D	->
Pop the location of an aggregate and an element from the program stack.
If the top of the data stack is true, add the element to the aggregate.
*/
void fpush_(pEnv env)
{
    int i;
    Node test, jump, elem, node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &test);
    env->prog = pvec_pop(env->prog, &jump);
    env->prog = pvec_pop(env->prog, &elem);
    if (test.u.num) {
	node = pvec_nth(env->prog, jump.u.num);
	switch (node.op) {
	case LIST_:
	    node.u.lis = pvec_add(node.u.lis, elem);
	    break;

	case STRING_:
	case BIGNUM_:
	case USR_STRING_:
	    i = strlen(node.u.str);
	    node.u.str[i++] = elem.u.num;
	    node.u.str[i] = 0;
	    break;

	case SET_:
	    node.u.set |= ((int64_t)1 << elem.u.num);
	    break;

	default:
	    break;
	}
	env->prog = pvec_upd(env->prog, jump.u.num, node);	/* write node */
    }
}
#endif
