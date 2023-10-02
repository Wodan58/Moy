/*
    module  : tpush.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef TPUSH_C
#define TPUSH_C

/**
OK 3390  (tpush)  :  D	->
Pop the location of two aggregates and an element from the program stack.
The element is added to one of the two aggregates, depending on the value
on top of the data stack.
*/
void tpush_(pEnv env)
{
    int i;
    Node test, jump, elem, node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &test);
    env->prog = pvec_pop(env->prog, &jump);
    env->prog = pvec_pop(env->prog, &elem);
    if (test.u.num)
	node = pvec_nth(env->prog, jump.u.num + 1);
    else
	node = pvec_nth(env->prog, jump.u.num); /* one step further away */
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
    if (test.u.num)
	env->prog = pvec_upd(env->prog, jump.u.num + 1, node);	/* write node */
    else
	env->prog = pvec_upd(env->prog, jump.u.num, node);	/* write node */
}
#endif
