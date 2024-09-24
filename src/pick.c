/*
    module  : pick.c
    version : 1.15
    date    : 09/17/24
*/
#ifndef PICK_C
#define PICK_C

/**
Q0  OK  3190  pick  :  DA  X Y Z 2  ->  X Y Z X
[EXT] Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
void pick_(pEnv env)
{
    int size;
    Node node;

    PARM(1, UNMKTIME);
    node = vec_pop(env->stck);
    size = vec_size(env->stck);
    if (node.u.num < size)
	node = vec_at(env->stck, size - node.u.num - 1);
    else
	node = vec_at(env->stck, 0);
    vec_push(env->stck, node);
}
#endif
