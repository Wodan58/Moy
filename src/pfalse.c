/*
    module  : pfalse.c
    version : 1.5
    date    : 09/15/23
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
    test = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    if (!test.u.num)
	lst_resize(env->prog, jump.u.num);
}
#endif
