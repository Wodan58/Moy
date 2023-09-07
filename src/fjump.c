/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#ifndef FJUMP_C
#define FJUMP_C

/**
OK 3420  (fjump)  :  D	->
Pop the jump location from the program stack. Pop the top of the data stack.
If the top of the stack was false, jump to the location in the program stack.
*/
void fjump_(pEnv env)
{
    Node test, jump;

    PARM(1, ANYTYPE);
    test = lst_pop(env->stck);
    jump = lst_pop(env->prog);
    if (!test.u.num)
        lst_resize(env->prog, jump.u.num);
}
#endif
