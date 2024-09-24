/*
    module  : fjump.c
    version : 1.10
    date    : 09/17/24
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
    test = vec_pop(env->stck);
    jump = vec_pop(env->prog);
    if (!test.u.num)
	vec_setsize(env->prog, jump.u.num);
}
#endif
