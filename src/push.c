/*
    module  : push.c
    version : 1.12
    date    : 03/05/24
*/
#ifndef PUSH_C
#define PUSH_C

/**
Q0  OK  3340  #push  :  D  ->
Pop the location of an aggregate from the program stack. Pop an element
from the data stack and add that element to the aggregate.
*/
void push_(pEnv env)
{
    int i;
    Node jump, elem, node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &elem);
    env->prog = pvec_pop(env->prog, &jump);
    node = pvec_nth(env->prog, jump.u.num);	/* read node */
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
    }
    env->prog = pvec_upd(env->prog, jump.u.num, node);	/* write node */
}
#endif
