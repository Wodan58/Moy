/* swap.c */
PRIVATE void swap_()
{
    Node temp, *node;

    TWOPARAMS("swap");
    temp = *stk;
    node = stk->next;
    if (OUTSIDE) {
	stk->u = node->u;
	stk->op = node->op;
	node->u = temp.u;
	node->op = temp.op;
	return;
    }
    GBINARY(temp.op, temp.u);
    GNULLARY(node->op, node->u);
}
