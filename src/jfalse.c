/*
    module  : jfalse.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef JFALSE_C
#define JFALSE_C

/**
OK 3340  (jfalse)  :  N	->
Pop the jump location from the program stack. If the top of the data stack
is false, jump to that location.
*/
void jfalse_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    test = vec_pop(env->stck);
    jump = vec_pop(env->prog);
    if (test.u.num != 1) {
        vec_resize(env->prog, jump.u.num);
        code(env, false_);
    }
}
#endif
