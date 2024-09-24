/*
    module  : treestep.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
Q1  OK  2870  treestep  :  DDA  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void treestep_(pEnv env)
{
    int i;
    Node list, node;
    vector(Node) *tree;

    PARM(2, DIP);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    vec_init(tree);
    for (i = vec_size(node.u.lis) - 1; i >= 0; i--)
	vec_push(tree, vec_at(node.u.lis, i));
    while (vec_size(tree)) {
	node = vec_pop(tree);
	if (node.op == LIST_)
	    for (i = vec_size(node.u.lis) - 1; i >= 0; i--)
		vec_push(tree, vec_at(node.u.lis, i));
	else {
	    prog(env, list.u.lis);
	    prime(env, node);
	}
    }
}
#endif
