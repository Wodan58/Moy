/*
    module  : sametype.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

/**
OK 3210  sametype  :  DDA	X Y  ->  B
[EXT] Tests whether X and Y have the same type.
*/
void sametype_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    if (first.op == ANON_FUNCT_) {
	if (env->bytecoding || env->compiling)
	    first.u.num = first.u.ent == second.u.ent;
        else
	    first.u.num = first.u.proc == second.u.proc;
    } else
	first.u.num = first.op == second.op;
    first.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, first);
}
#endif
