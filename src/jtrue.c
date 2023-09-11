/*
    module  : jtrue.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef JTRUE_C
#define JTRUE_C

/**
OK 3410  (jtrue)  :  N	->
Pop the jump location from the program stack. If the top of the data stack
is true, jump to that location.
*/
void jtrue_(pEnv env)
{
#ifndef COMPILER
    Node test, jump;

    PARM(1, ANYTYPE);
    test = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    if (test.u.num != 0) {
	lst_resize(env->prog, jump.u.num);
	code(env, true_);
    }
#endif
}
#endif
