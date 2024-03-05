/*
    module  : and.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef AND_C
#define AND_C

/**
Q0  OK  1360  and  :  DDA  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
void and_(pEnv env)
{
    Node first, second;

    PARM(2, ANDORXOR);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case SET_:
	first.u.set &= second.u.set;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	first.u.num = first.u.num && second.u.num;
	first.op = BOOLEAN_;
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
