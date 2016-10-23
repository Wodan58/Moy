/*
    module  : copy.c
    version : 1.4
    date    : 10/16/16
*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "globals1.h"

void copy2(Node *cur, int i)
{
    if (cur->next && i > 1)
	copy2(cur->next, i - 1);
    GNULLARY(cur->op, cur->u.ptr);
}

void copy_(int cnt)
{
    int i, j, k;

    if (!cnt)
	return;
    if (OUTSIDE && INSIDE) {
	j = &memory[MEMORYMAX] - stk;
	if (!j)
	    return;
	if (cnt == MEMORYMAX)
	    cnt = j;
	if (cnt > j)
	    cnt = j;
	k = stk - memory;
	j = cnt;
	if (j > k) {
	    j = k;
	    cnt -= j;
	}
	for (i = 0; i < j; i++) {
	    stk[i - cnt].u = stk[i].u;
	    stk[i - cnt].op = stk[i].op;
	}
	stk -= j;
    }
    if (cnt > 0)
	copy2(stk, cnt);
}
