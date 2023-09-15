/*
    module  : opcase.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
OK 2090  opcase  :  DA	X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void opcase_(pEnv env)
{
    int i;
    Node node, aggr, elem, temp;

    PARM(2, CASE);
    aggr = lst_pop(env->stck);
    node = lst_back(env->stck);
    for (i = lst_size(aggr.u.lis) - 1; i >= 0; i--) {
	elem = lst_at(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	temp = lst_back(elem.u.lis);
	if (node.op == temp.op) {
	    if (node.op == ANON_FUNCT_ && node.u.proc != temp.u.proc)
		;
	    else {
		lst_init(node.u.lis);
		lst_shallow_copy(node.u.lis, elem.u.lis);
		(void)lst_pop(node.u.lis);
		node.op = LIST_;
		break;
	    }
	}
    }
    lst_push(env->stck, node);
}
#endif
