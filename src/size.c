/*
    module  : size.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_size(void)
{
    TRACE;
    stk[-1] = joy_leng((code_t *)stk[-1]);
}
#else
/**
size  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
PRIVATE void do_size(void)
{
    int i;
    Node *cur;
    size_t size = 0;

#ifndef NCHECK
    if (compiling && AGGREGATE_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("size");
    switch (stk->op) {
    case LIST_:
	for (cur = stk->u.lis; cur; cur = cur->next)
	    size++;
	break;
    case STRING_:
	size = strlen(stk->u.str);
	break;
    case SET_:
	for (i = 0; i < SETSIZE_; i++)
	    if (stk->u.set & (1 << i))
		size++;
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("size");
#endif
    }
    if (OUTSIDE) {
	stk->u.num = size;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, size);
}
#endif
