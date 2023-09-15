/*
    module  : __manual_list.c
    version : 1.6
    date    : 09/15/23
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

    lst_init(node.u.lis);
    node.op = temp.op = LIST_;
    elem.op = STRING_;
    for (i = 0; (tab = readtable(i)) != 0; i++) /* find end */
	;
    while (--i) {
	tab = readtable(i);
	lst_init(temp.u.lis);
	elem.u.str = tab->messg2;
	lst_push(temp.u.lis, elem);
	elem.u.str = tab->messg1;
	lst_push(temp.u.lis, elem);
	elem.u.str = tab->name;
	lst_push(temp.u.lis, elem);
	lst_push(node.u.lis, temp);
    }
    lst_push(env->stck, node);
}
#endif
