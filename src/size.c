/*
    module  : size.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef SIZE_C
#define SIZE_C

/**
size  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
PRIVATE void do_size(void)
{
    int i;
    Node *cur;
    size_t size = 0;

#ifndef OLD_RUNTIME
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
	    if (stk->u.set & ((long_t)1 << i))
		size++;
	break;
    default:
	BADAGGREGATE("size");
	break;
    }
    stk->u.num = size;
    stk->op = INTEGER_;
}
#endif
