/*
    module  : __manual_list.c
    version : 1.12
    date    : 07/02/24
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
Q0  OK  2960  __manual_list  :  A  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
void __manual_list_(pEnv env)
{
    int i;
    Node node, temp, elem;

    node.u.lis = pvec_init();
    node.op = temp.op = LIST_;
    elem.op = STRING_;
    for (i = sizeof(optable) / sizeof(optable[0]) - 1; i >= 0; i--) {
	temp.u.lis = pvec_init();
	elem.u.str = optable[i].messg2;
	temp.u.lis = pvec_add(temp.u.lis, elem);
	elem.u.str = optable[i].messg1;
	temp.u.lis = pvec_add(temp.u.lis, elem);
	elem.u.str = optable[i].name;
	temp.u.lis = pvec_add(temp.u.lis, elem);
	node.u.lis = pvec_add(node.u.lis, temp);
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
