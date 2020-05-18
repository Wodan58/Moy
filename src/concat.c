/*
    module  : concat.c
    version : 1.14
    date    : 03/28/20
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
concat  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
PRIVATE void do_concat(void)
{
    char *str;
    unsigned i;
    Node *cur = 0, *root = 0, *last = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_2 && AGGREGATE_1 && AGGREGATE_2 &&
	stk->op == stk->next->op)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("concat");
    SAME2TYPES("concat");
    switch (stk->op) {
    case LIST_:
	if (!stk->next->u.lis) {
	    stk->next->u.lis = stk->u.lis;
	    POP(stk);
	    return;
	}
	for (cur = stk->next->u.lis; cur; cur = cur->next)
	    if (!root)
		last = root = newnode(cur->op, cur->u.ptr, 0);
	    else
		last = last->next = newnode(cur->op, cur->u.ptr, 0);
	last->next = stk->u.lis;
	stk->next->u.lis = root;
	POP(stk);
	break;
    case STRING_:
	i = strlen(stk->next->u.str);
	str = ck_malloc_sec(i + strlen(stk->u.str) + 1);
	strcpy(str, stk->next->u.str);
	strcpy(str + i, stk->u.str);
	stk->next->u.str = str;
	POP(stk);
	break;
    case SET_:
	stk->next->u.set |= stk->u.set;
	POP(stk);
	break;
    default:
	BADAGGREGATE("concat");
	break;
    }
}
#endif
