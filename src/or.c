/*
    module  : or.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef OR_C
#define OR_C

/**
Q0  OK  1340  or  :  DDA  X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
void or_(pEnv env)
{
    Node first, second;

    PARM(2, ANDORXOR);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case SET_:
	first.u.set = first.u.set | second.u.set;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	first.u.num = first.u.num || second.u.num;
	first.op = BOOLEAN_;
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
