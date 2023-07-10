/*
    module  : not.c
    version : 1.1
    date    : 07/10/23
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
    default:
        break;
    }
    vec_push(env->stck, node);
}
#endif
