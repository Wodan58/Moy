/*
    module  : jfalse.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef JFALSE_C
#define JFALSE_C

/**
Q0  OK  3390  #jfalse  :  N  ->
Pop the jump location from the program stack. If the top of the data stack
is false, jump to that location.
*/
void jfalse_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &test);
    env->prog = pvec_pop(env->prog, &jump);
    if (test.u.num != 1) {
	env->prog = pvec_cut(env->prog, jump.u.num);
	code(env, false_);
    }
}
#endif
