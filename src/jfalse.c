/*
    module  : jfalse.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef JFALSE_C
#define JFALSE_C

/**
OK 3400  (jfalse)  :  N	->
Pop the jump location from the program stack. If the top of the data stack
is false, jump to that location.
*/
void jfalse_(pEnv env)
{
#ifndef COMPILER
    Node test, jump;

    PARM(1, ANYTYPE);
    test = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    if (test.u.num != 1) {
	lst_resize(env->prog, jump.u.num);
	code(env, false_);
    }
#endif
}
#endif
