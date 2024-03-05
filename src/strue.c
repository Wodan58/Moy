/*
    module  : strue.c
    version : 1.10
    date    : 03/05/24
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
    env->stck = pvec_pop(env->stck, &test);
    env->prog = pvec_pop(env->prog, &jump);
    if (test.u.num) {
	env->prog = pvec_cut(env->prog, jump.u.num);
	code(env, true_);
    }
}
#endif
