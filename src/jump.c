/*
    module  : jump.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef JUMP_C
#define JUMP_C

/**
OK 3260  (jump)  :  N	->
Pop the jump location from the program stack. Jump to that location.
*/
void jump_(pEnv env)
{
    Node jump;

    jump = vec_pop(env->prog);
    vec_resize(env->prog, jump.u.num);
}
#endif
