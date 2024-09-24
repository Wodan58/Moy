/*
    module  : not.c
    version : 1.9
    date    : 09/17/24
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
    node = vec_pop(env->stck);
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
    vec_push(env->stck, node);
}
#endif
