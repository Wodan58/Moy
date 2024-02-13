/*
    module  : pick.c
    version : 1.12
    date    : 02/05/24
*/
#ifndef PICK_C
#define PICK_C

/**
OK 3180  pick  :  DA	X Y Z 2  ->  X Y Z X
[EXT] Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
void pick_(pEnv env)
{
    int size;
    Node node;

    PARM(1, UNMKTIME);
    env->stck = pvec_pop(env->stck, &node);
    size = pvec_cnt(env->stck);
    if (node.u.num < size)
	node = pvec_nth(env->stck, size - node.u.num - 1);
    else
	node = pvec_nth(env->stck, 0);
    env->stck = pvec_add(env->stck, node);
}
#endif
