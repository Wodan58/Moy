/*
    module  : setautoput.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SETAUTOPUT_C
#define SETAUTOPUT_C

/**
OK 3000 setautoput  :  D	I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
void setautoput_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    env->autoput = node.u.num;
}
#endif
