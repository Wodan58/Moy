/*
    module  : push.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef PUSH_C
#define PUSH_C

/**
OK 3340  (push)  :  D	->
Pop the location of an aggregate from the program stack. Pop an element
from the data stack and add that element to the aggregate.
*/
void push_(pEnv env)
{
    int i;
    Node jump, elem, node;

    PARM(1, ANYTYPE);
    elem = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    node = lst_at(env->prog, jump.u.num); /* read node */
    switch (node.op) {
    case LIST_:
	lst_push(node.u.lis, elem);
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
    lst_assign(env->prog, jump.u.num, node); /* write node */
}
#endif
