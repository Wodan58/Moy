/*
    module  : case.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef CASE_C
#define CASE_C

#include "compare.h"

/**
OK 2100  case  :  DDU	X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
void case_(pEnv env)
{
    int i;
    Node node, aggr, elem;

    PARM(2, CASE);
    aggr = lst_pop(env->stck);
    node = lst_back(env->stck);
    for (i = lst_size(aggr.u.lis) - 1; i >= 0; i--) {
	elem = lst_at(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	if (!Compare(env, node, lst_back(elem.u.lis))) {
	    lst_init(node.u.lis);
	    lst_shallow_copy(node.u.lis, elem.u.lis);
	    (void)lst_pop(node.u.lis);
	    (void)lst_pop(env->stck);
	    break;
	}
    }
    prog(env, node.u.lis);
}
#endif
