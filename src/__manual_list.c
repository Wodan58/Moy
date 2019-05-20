/*
    module  : __manual_list.c
    version : 1.7
    date    : 05/18/19
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
	tmp = newnode(STRING_, (void *)optable[i].messg2, 0);
	tmp = newnode(STRING_, (void *)optable[i].messg1, tmp);
	tmp = newnode(STRING_, (void *)optable[i].name, tmp);
	cur = newnode(LIST_, (void *)tmp, cur);
    }
    PUSH(LIST_, cur);
}
#endif
#endif
