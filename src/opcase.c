/*
    module  : opcase.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
OK 2100  opcase  :  DA	X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void opcase_(pEnv env)
{
    int i;
    Node node, aggr, elem, temp;

    PARM(2, CASE);
    aggr = vec_pop(env->stck);
    node = vec_back(env->stck);
    for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
        elem = vec_at(aggr.u.lis, i);
        if (!i) {
            node = elem;
            break;
        }
        temp = vec_back(elem.u.lis);
        if (node.op == temp.op) {
            if (node.op == ANON_FUNCT_ && node.u.proc != temp.u.proc)
                ;
            else {
                vec_init(node.u.lis);
                vec_shallow_copy(node.u.lis, elem.u.lis);
                (void)vec_pop(node.u.lis);
                node.op = LIST_;
                break;
            }
        }
    }
    vec_push(env->stck, node);
}
#endif
