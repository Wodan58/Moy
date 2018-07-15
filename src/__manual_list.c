/*
    module  : __manual_list.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef __MANUAL_LIST_X
#define __MANUAL_LIST_C

#ifdef NEW_RUNTIME
void do___manual_list(void)
{
    TRACE;
}
#else
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
	tmp = heapnode(STRING_, (void *)optable[i].messg2, 0);
	tmp = heapnode(STRING_, (void *)optable[i].messg1, tmp);
	tmp = heapnode(STRING_, (void *)optable[i].name, tmp);
	cur = heapnode(LIST_, (void *)tmp, cur);
    }
    PUSH(LIST_, cur);
}
#endif
#endif
