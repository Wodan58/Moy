/*
    module  : sametype.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

/**
OK 3240  sametype  :  DDA	X Y  ->  B
[EXT] Tests whether X and Y have the same type.
*/
void sametype_(pEnv env)
{
#ifndef COMPILER
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    if (first.op == ANON_FUNCT_)
	node.u.num = first.u.proc == second.u.proc;
    else
	node.u.num = first.op == second.op;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
#endif
}
#endif
