/*
    module  : jtrue.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef JTRUE_C
#define JTRUE_C

/**
OK 3350  (jtrue)  :  N	->
Pop the jump location from the program stack. If the top of the data stack
is true, jump to that location.
*/
void jtrue_(pEnv env)
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
