/*
    module  : treestep.c
    version : 1.8
    date    : 11/06/23
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
OK 2870  treestep  :  DDA	T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void treestep_(pEnv env)
{
    int i;
    Node list, node;
    vector(Node) *tree;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node);
    vec_init(tree);
    for (i = pvec_cnt(node.u.lis) - 1; i >= 0; i--)
	vec_push(tree, pvec_nth(node.u.lis, i));
    while (vec_size(tree)) {
	node = vec_pop(tree);
	if (node.op == LIST_)
	    for (i = pvec_cnt(node.u.lis) - 1; i >= 0; i--)
		vec_push(tree, pvec_nth(node.u.lis, i));
	else {
	    prog(env, list.u.lis);
	    prime(env, node);
	}
    }
}
#endif
