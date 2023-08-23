/*
    module  : __manual_list.c
    version : 1.3
    date    : 08/23/23
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
OK 2980  __manual_list  :  A	->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
void __manual_list_(pEnv env)
{
    int i;
    Node node, temp, elem;

    lst_init(node.u.lis);
    node.op = temp.op = LIST_;
    elem.op = STRING_;
    i = sizeof(optable) / sizeof(optable[0]); /* find end */
    while (--i) {
        lst_init(temp.u.lis);
        elem.u.str = optable[i].messg2;
        lst_push(temp.u.lis, elem);
        elem.u.str = optable[i].messg1;
        lst_push(temp.u.lis, elem);
        elem.u.str = optable[i].name;
        lst_push(temp.u.lis, elem);
        lst_push(node.u.lis, temp);
    }
    lst_push(env->stck, node);
}
#endif
