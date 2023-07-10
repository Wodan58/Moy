/*
    module  : unswons.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
OK 2130  unswons  :  DAA	A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void unswons_(pEnv env)
{
    int i = 0;
    Node node, temp;

    PARM(1, FIRST);
    node = vec_pop(env->stck);
    switch (node.op) {
    case LIST_:
        vec_init(temp.u.lis);
        vec_shallow_copy(temp.u.lis, node.u.lis);
        node = vec_pop(temp.u.lis);
        temp.op = LIST_;
        vec_push(env->stck, temp);
        vec_push(env->stck, node);
        break;

    case STRING_:
        temp.u.num = *node.u.str++;
        node.u.str = GC_strdup(node.u.str);  
        vec_push(env->stck, node);
        temp.op = CHAR_;
        vec_push(env->stck, temp);
        break;

    case SET_:
        while (!(node.u.set & ((long)1 << i)))
            i++;
        temp.u.num = i;
        node.u.set &= ~((long)1 << i);
        vec_push(env->stck, node);
        temp.op = INTEGER_;
        vec_push(env->stck, temp);
    default:
        break;
    }
}
#endif
