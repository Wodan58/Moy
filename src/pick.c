/*
    module  : pick.c
    version : 1.3
    date    : 08/23/23
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
    node = lst_pop(env->stck);
    size = lst_size(env->stck);
    if (node.u.num < size) {
        temp = lst_at(env->stck, size - node.u.num - 1);
        lst_push(env->stck, temp);
    }
}
#endif
