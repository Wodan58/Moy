/*
    module  : treestep.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
OK 2890  treestep  :  DDU	T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void treestep_(pEnv env)
{
    int i;
    NodeList *tree = 0;
    Node aggr, list, node, temp;

    PARM(2, DIP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    vec_init(tree);
    for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
        temp = vec_at(aggr.u.lis, i);
        vec_push(tree, temp);
    }
    while (vec_size(tree)) {
        node = vec_pop(tree);
        if (node.op != LIST_) {
            prog(env, list.u.lis);
            prime(env, node);
        } else {
            for (i = vec_size(node.u.lis) - 1; i >= 0; i--) {
                temp = vec_at(node.u.lis, i);
                vec_push(tree, temp);
            }
        }
    }
}
#endif
