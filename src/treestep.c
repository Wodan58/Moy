/*
    module  : treestep.c
    version : 1.3
    date    : 08/23/23
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
    Node list, node, temp;

    PARM(2, DIP);
    list = lst_pop(env->stck);
    node = lst_pop(env->stck);
    lst_init(tree);
    for (i = lst_size(node.u.lis) - 1; i >= 0; i--) {
        temp = lst_at(node.u.lis, i);
        lst_push(tree, temp);
    }
    while (lst_size(tree)) {
        node = lst_pop(tree);
        if (node.op != LIST_) {
            prog(env, list.u.lis);
            prime(env, node);
        } else {
            for (i = lst_size(node.u.lis) - 1; i >= 0; i--) {
                temp = lst_at(node.u.lis, i);
                lst_push(tree, temp);
            }
        }
    }
}
#endif
