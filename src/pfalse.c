/*
    module  : pfalse.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef PFALSE_C
#define PFALSE_C

/**
OK 3370  (pfalse)  :  D	->
Pop the jump location from the program stack. Pop the condition from the data
stack. If the condition is false, jump to the location.
*/
void pfalse_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &test);
    env->prog = pvec_pop(env->prog, &jump);
    if (!test.u.num)
	env->prog = pvec_cut(env->prog, jump.u.num);
}
#endif
