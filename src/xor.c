/*
    module  : xor.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef XOR_C
#define XOR_C

/**
Q0  OK  1350  xor  :  DDA  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
void xor_(pEnv env)
{
    Node first, second;

    PARM(2, ANDORXOR);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
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
    }
    vec_push(env->stck, first);
}
#endif
