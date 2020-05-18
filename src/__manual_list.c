/*
    module  : __manual_list.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
__manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
PRIVATE void do___manual_list(void)
{
    int i = -1;
    Node *tmp, *cur = 0;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    while (optable[++i].name);
    while (--i) {
	tmp = newnode(STRING_, (void *)optable[i].messg2, 0);
	tmp = newnode(STRING_, (void *)optable[i].messg1, tmp);
	tmp = newnode(STRING_, (void *)optable[i].name, tmp);
	cur = newnode(LIST_, (void *)tmp, cur);
    }
    PUSH(LIST_, cur);
}
#endif
