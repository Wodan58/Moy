/* unstack.c */
PRIVATE void unstack_()
{
    Node *cur;

    ONEPARAM("unstack");
    LIST("unstack");
    for (cur = reverse(stk->u.lis), stk = 0; cur; cur = cur->next)
	DUPLICATE(cur);
}
