/*
    module  : __manual_list.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

extern optable_t optable[];

/**
__manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
PRIVATE void do___manual_list(void)
{
    int i = -1;
    Node *tmp, *cur = 0;

#ifndef NCHECK
    if (optimizing)
	add_history2(LIST_, LIST_);
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
