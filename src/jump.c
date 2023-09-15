/*
    module  : jump.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef JUMP_C
#define JUMP_C

/**
OK 3320  (jump)  :  N	->
Pop the jump location from the program stack. Jump to that location.
*/
void jump_(pEnv env)
{
    Node jump;

    jump = lst_pop(env->prog);
    lst_resize(env->prog, jump.u.num);
}
#endif
