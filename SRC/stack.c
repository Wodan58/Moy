/* stack.c */
PRIVATE void stack_(void)
{
    Node *cur, *node = 0;

    for (cur = stk; cur; cur = cur->next)
	node = newnode(cur->op, cur->u, node);
    PUSH(LIST_, reverse(node));
}
