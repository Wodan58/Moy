/*
    module  : size.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SIZE_C
#define SIZE_C

/**
OK 2090  size  :  DA	A  ->  I
Integer I is the number of elements of aggregate A.
*/
void size_(pEnv env)
{
    int i;
    Node node, temp;

    PARM(1, SIZE);
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
        temp.u.num = vec_size(node.u.lis);
        break;
    case STRING_:
        temp.u.num = strlen(node.u.str);
        break;
    case SET_:
        for (i = 0, temp.u.num = 0; i < SETSIZE; i++)
            if (node.u.set & ((long)1 << i))
                temp.u.num++;
    default:
        break;
    }
    temp.op = INTEGER_;
    vec_push(env->stck, temp);
}
#endif
