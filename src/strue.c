/*
    module  : strue.c
    version : 1.6
    date    : 09/19/23
*/
#ifndef STRUE_C
#define STRUE_C

/**
OK 3410  (strue)  :  N	->
Pop the jump location from the program stack. If the top of the data stack
is true, jump to that location.
*/
void strue_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    test = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    if (test.u.num != 0) {
	lst_resize(env->prog, jump.u.num);
	code(env, true_);
    }
}
#endif
