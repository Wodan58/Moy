/*
    module  : concat.c
    version : 1.12
    date    : 07/15/18
*/
#ifndef CONCAT_X
#define CONCAT_C

#ifdef NEW_RUNTIME
void do_concat(void)
{
    code_t *first, *second, *root = 0, *cur = 0;

    TRACE;
    second = (code_t *)do_pop();
    first = (code_t *)stk[-1];
    for (; first; first = first->next) {
	if (!root)
	    cur = root = joy_code();
	else
	    cur = cur->next = joy_code();
	cur->num = first->num;
    }
    if (cur)
	cur->next = second;
    else
	root = second;
    stk[-1] = (node_t)root;
}
#else
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
	    if (OUTSIDE) {
		stk->next->u.lis = stk->u.lis;
		POP(stk);
	    } else
	        BINARY(LIST_NEWNODE, stk->u.lis);
	    return;
	}
	for (cur = stk->next->u.lis; cur; cur = cur->next)
	    if (!root)
		last = root = heapnode(cur->op, cur->u.ptr, 0);
	    else
		last = last->next = heapnode(cur->op, cur->u.ptr, 0);
	last->next = stk->u.lis;
	if (OUTSIDE) {
	    stk->next->u.lis = root;
	    POP(stk);
	} else
	    BINARY(LIST_NEWNODE, root);
	break;
    case STRING_:
	i = strlen(stk->next->u.str);
	str = ck_malloc_sec(i + strlen(stk->u.str) + 1);
	strcpy(str, stk->next->u.str);
	strcpy(str + i, stk->u.str);
	if (OUTSIDE) {
	    stk->next->u.str = str;
	    POP(stk);
	} else
	    BINARY(STRING_NEWNODE, str);
	break;
    case SET_:
	if (OUTSIDE) {
	    stk->next->u.set |= stk->u.set;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, stk->next->u.set | stk->u.set);
	break;
    default:
	BADAGGREGATE("concat");
	break;
    }
}
#endif
#endif
