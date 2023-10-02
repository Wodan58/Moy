/*
    module  : pick.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef PICK_C
#define PICK_C

/**
OK 3220  pick  :  DA	X Y Z 2  ->  X Y Z X
[EXT] Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
void pick_(pEnv env)
{
    int size;
    Node node;

    PARM(1, UNMKTIME);
    env->stck = pvec_pop(env->stck, &node);
    size = pvec_cnt(env->stck);
    if (node.u.num < size) {
	node = pvec_nth(env->stck, size - node.u.num - 1);
	env->stck = pvec_add(env->stck, node);
    }
}
#endif
