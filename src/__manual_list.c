/*
    module  : __manual_list.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
OK 2960  __manual_list  :  A	->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
void __manual_list_(pEnv env)
{
    int i;
    OpTable *tab;
    Node node, temp, elem;

    node.u.lis = pvec_init();
    node.op = temp.op = LIST_;
    elem.op = STRING_;
    for (i = 0; (tab = readtable(i)) != 0; i++) /* find end */
	;
    while (--i) {
	tab = readtable(i);
	temp.u.lis = pvec_init();
	elem.u.str = tab->messg2;
	temp.u.lis = pvec_add(temp.u.lis, elem);
	elem.u.str = tab->messg1;
	temp.u.lis = pvec_add(temp.u.lis, elem);
	elem.u.str = tab->name;
	temp.u.lis = pvec_add(temp.u.lis, elem);
	node.u.lis = pvec_add(node.u.lis, temp);
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
