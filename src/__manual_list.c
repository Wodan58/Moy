/*
    module  : __manual_list.c
    version : 1.13
    date    : 09/17/24
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

    vec_init(node.u.lis);
    node.op = temp.op = LIST_;
    elem.op = STRING_;
    for (i = sizeof(optable) / sizeof(optable[0]) - 1; i >= 0; i--) {
        vec_init(temp.u.lis);
	elem.u.str = optable[i].messg2;
        vec_push(temp.u.lis, elem);
	elem.u.str = optable[i].messg1;
        vec_push(temp.u.lis, elem);
	elem.u.str = optable[i].name;
        vec_push(temp.u.lis, elem);
        vec_push(node.u.lis, temp);
    }
    vec_push(env->stck, node);
}
#endif
