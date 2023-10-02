/*
    module  : not.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef NOT_C
#define NOT_C

/**
OK 1370  not  :  DA	X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
void not_(pEnv env)
{
    Node node;

    PARM(1, NOT);
    env->stck = pvec_pop(env->stck, &node);
    switch (node.op) {
    case SET_:
	node.u.set = ~node.u.set;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	node.u.num = !node.u.num;
	node.op = BOOLEAN_;
	break;
    default:
	break;
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
