/*
    module  : strue.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef STRUE_C
#define STRUE_C

/**
Q0  OK  3400  #strue  :  N  ->
Pop the jump location from the program stack. If the top of the data stack
is true, jump to that location.
*/
void strue_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    test = vec_pop(env->stck);
    jump = vec_pop(env->prog);
    if (test.u.num) {
	vec_setsize(env->prog, jump.u.num);
	code(env, true_);
    }
}
#endif
