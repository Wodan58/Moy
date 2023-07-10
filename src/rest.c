/*
    module  : rest.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef REST_C
#define REST_C

/**
OK 2050  rest  :  DA	A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void rest_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
        vec_init(temp.u.lis);
        vec_shallow_copy(temp.u.lis, node.u.lis);
        (void)vec_pop(temp.u.lis);
        temp.op = LIST_;
        vec_push(env->stck, temp);
        break;

    case STRING_:
        node.u.str = GC_strdup(++node.u.str);  
        vec_push(env->stck, node);
        break;

    case SET_:
        while (!(node.u.set & ((long)1 << i)))
            i++;
        node.u.set &= ~((long)1 << i);
        vec_push(env->stck, node);
    default:
        break;
    }
}
#endif
