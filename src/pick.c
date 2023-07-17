/*
    module  : pick.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef PICK_C
#define PICK_C

/**
OK 3230  pick  :  DA	X Y Z 2  ->  X Y Z X
Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
void pick_(pEnv env)
{
    int size;
    Node node, temp;

    PARM(1, UNMKTIME);
    node = vec_pop(env->stck);
    size = vec_size(env->stck);
    if (node.u.num < size) {
        temp = vec_at(env->stck, size - node.u.num - 1);
        vec_push(env->stck, temp);
    }
}
#endif
