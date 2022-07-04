/*
    module  : __manual_list.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
__manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
PRIVATE void do___manual_list(pEnv env)
{
#ifdef COMPILING
    int i = -1;
    Node *tmp, *cur = 0;

    COMPILE;
    while (optable[++i].name);
    while (--i) {
	tmp = STRING_NEWNODE(optable[i].messg2, 0);
	tmp = STRING_NEWNODE(optable[i].messg1, tmp);
	tmp = STRING_NEWNODE(optable[i].name, tmp);
	cur = LIST_NEWNODE(tmp, cur);
    }
    PUSH_PTR(LIST_, cur);
#endif
}
#endif
