/*
    module  : autoput.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef AUTOPUT_C
#define AUTOPUT_C

/**
OK 1090  autoput  :  A	->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
void autoput_(pEnv env)
{
    Node node;

    node.u.num = env->autoput;
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
