/*
    module  : setautoput.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef SETAUTOPUT_C
#define SETAUTOPUT_C

/**
OK 2980  setautoput  :  D	I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
void setautoput_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = lst_pop(env->stck);
    env->autoput = node.u.num;
}
#endif
