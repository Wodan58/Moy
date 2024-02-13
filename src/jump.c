/*
    module  : jump.c
    version : 1.8
    date    : 01/24/24
*/
#ifndef JUMP_C
#define JUMP_C

/**
OK 3320  #jump  :  N	->
Pop the jump location from the program stack. Jump to that location.
*/
void jump_(pEnv env)
{
    Node jump;

    env->prog = pvec_pop(env->prog, &jump);
    env->prog = pvec_cut(env->prog, jump.u.num);
}
#endif
