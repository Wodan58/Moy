/*
    module  : xor.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef XOR_C
#define XOR_C

/**
OK 1350  xor  :  DDA	X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
void xor_(pEnv env)
{
    Node first, second;

    PARM(2, ANDORXOR);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case SET_:
	first.u.set = first.u.set ^ second.u.set;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	first.u.num = first.u.num != second.u.num;
	first.op = BOOLEAN_;
	break;
    default:
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
