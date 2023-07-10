/*
    module  : first.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FIRST_C
#define FIRST_C

/**
OK 2040  first  :  DA	A  ->  F
F is the first member of the non-empty aggregate A.
*/
void first_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
        temp = vec_back(node.u.lis);
        vec_push(env->stck, temp);
        break;

    case STRING_:
        temp.u.num = *node.u.str;
        temp.op = CHAR_;
        vec_push(env->stck, temp);
        break;

    case SET_:
        while (!(node.u.set & ((long)1 << i)))
            i++;
        temp.u.num = i;
        temp.op = INTEGER_;
        vec_push(env->stck, temp);
    default:
        break;
    }
}
#endif
