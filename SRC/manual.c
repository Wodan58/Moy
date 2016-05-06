/*
    module  : manual.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/* manual.c */
PRIVATE void manual_list_(void)
{
    int i = -1;
    Node *tmp, *cur = 0;

    while (optable[++i].name);
    while (--i) {
	tmp = newnode(STRING_, optable[i].messg2, 0);
	tmp = newnode(STRING_, optable[i].messg1, tmp);
	tmp = newnode(STRING_, optable[i].name, tmp);
	cur = newnode(LIST_, tmp, cur);
    }
    PUSH(LIST_, cur);
}
