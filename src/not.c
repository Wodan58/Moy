/*
    module  : not.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef NOT_C
#define NOT_C

/**
Q0  OK  1370  not  :  DA  X  ->  Y
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
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
