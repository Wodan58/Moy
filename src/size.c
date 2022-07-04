/*
    module  : size.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef SIZE_C
#define SIZE_C

/**
size  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
PRIVATE void do_size(pEnv env)
{
    int i;
    Node *cur;
    size_t size = 0;

    ONEPARAM("size");
    switch (env->stk->op) {
    case LIST_:
	for (cur = env->stk->u.lis; cur; cur = cur->next)
	    size++;
	break;
    case STRING_:
	size = strlen(env->stk->u.str);
	break;
    case SET_:
	for (i = 0; i < SETSIZE_; i++)
	    if (env->stk->u.set & ((long)1 << i))
		size++;
	break;
    default:
	BADAGGREGATE("size");
	break;
    }
    UNARY(INTEGER_NEWNODE, size);
}
#endif
