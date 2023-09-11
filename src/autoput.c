/*
    module  : autoput.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
OK 1090  autoput  :  A	->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
void autoput_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = env->autoput;
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
