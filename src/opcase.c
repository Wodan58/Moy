/*
    module  : opcase.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
Q0  OK  2090  opcase  :  DA  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void opcase_(pEnv env)
{
    int i;
    Node aggr, node, elem, temp;

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
	    if (node.op == ANON_FUNCT_) {
		if (node.u.proc != temp.u.proc)
		    continue;
	    }
            vec_shallow_copy(node.u.lis, elem.u.lis);
            (void)vec_pop(node.u.lis);
	    node.op = LIST_;
	    break;
	}
    }
    vec_push(env->stck, node);
}
#endif
