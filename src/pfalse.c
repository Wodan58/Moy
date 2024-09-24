/*
    module  : pfalse.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef PFALSE_C
#define PFALSE_C

/**
Q0  OK  3370  #pfalse  :  D  ->
Pop the jump location from the program stack. Pop the condition from the data
stack. If the condition is false, jump to that location.
*/
void pfalse_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    test = vec_pop(env->stck);
    jump = vec_pop(env->prog);
    if (!test.u.num)
	vec_setsize(env->prog, jump.u.num);
}
#endif
