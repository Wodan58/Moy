/*
    module  : fjump.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef FJUMP_C
#define FJUMP_C

/**
Q0  OK  3420  #fjump  :  D  ->
Pop the jump location from the program stack. Pop the top of the data stack.
If the top of the stack was false, jump to the location in the program stack.
*/
void fjump_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &test);
    env->prog = pvec_pop(env->prog, &jump);
    if (!test.u.num)
	env->prog = pvec_cut(env->prog, jump.u.num);
}
#endif
