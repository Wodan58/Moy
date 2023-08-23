/*
    module  : mktime.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef MKTIME_C
#define MKTIME_C

/**
OK 1720  mktime  :  DA	T  ->  I
Converts a list T representing local time into a time I.
T is in the format generated by localtime.
*/
void mktime_(pEnv env)
{
    Node node;
    struct tm t;

    PARM(1, HELP);
    node = lst_pop(env->stck);
    dtime(node, &t);
    node.u.num = mktime(&t);
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
