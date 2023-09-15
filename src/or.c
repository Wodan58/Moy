/*
    module  : or.c
    version : 1.5
    date    : 09/15/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
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
    default:
	break;
    }
    lst_push(env->stck, first);
}
#endif
