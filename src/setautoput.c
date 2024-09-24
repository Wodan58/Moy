/*
    module  : setautoput.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef SETAUTOPUT_C
#define SETAUTOPUT_C

/**
Q0  IGNORE_POP  2980  setautoput  :  D  I  ->
[IMPURE] Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
void setautoput_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    node = vec_pop(env->stck);
    if (!env->autoput_set)
	env->autoput = node.u.num;
}
#endif
