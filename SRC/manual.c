/*
    module  : manual.c
    version : 1.3
    date    : 10/04/16
*/
#include "interp.h"

/* manual.c */
PRIVATE void manual_list_(void)
{
    int i = -1;
    Node *tmp, *cur = 0;

    while (optable[++i].name);
    while (--i) {
	tmp = heapnode(STRING_, optable[i].messg2, 0);
	tmp = heapnode(STRING_, optable[i].messg1, tmp);
	tmp = heapnode(STRING_, optable[i].name, tmp);
	cur = heapnode(LIST_, tmp, cur);
    }
    PUSH(LIST_, cur);
}
