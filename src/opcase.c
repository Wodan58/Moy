/*
    module  : opcase.c
    version : 1.6
    date    : 10/02/23
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
    Node aggr, node, elem, temp;

    PARM(2, CASE);
    env->stck = pvec_pop(env->stck, &aggr);
    node = pvec_lst(env->stck);
    for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	elem = pvec_nth(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	temp = pvec_lst(elem.u.lis);
	if (node.op == temp.op) {
	    if (node.op == ANON_FUNCT_ && node.u.proc != temp.u.proc)
		;
	    else {
		node.u.lis = pvec_init();
		pvec_shallow_copy(node.u.lis, elem.u.lis);
		node.u.lis = pvec_del(elem.u.lis);
		node.op = LIST_;
		break;
	    }
	}
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
