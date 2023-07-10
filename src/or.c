/*
    module  : or.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef OR_C
#define OR_C

/**
OK 1340  or  :  DDA	X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
void or_(pEnv env)
{
    Node first, second;

    PARM(2, ANDORXOR);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    switch (first.op) {
    case SET_:
        first.u.set = first.u.set | second.u.set;
        break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
        first.u.num = first.u.num || second.u.num;
        first.op = BOOLEAN_;
    default:
        break;
    }
    vec_push(env->stck, first);
}
#endif
