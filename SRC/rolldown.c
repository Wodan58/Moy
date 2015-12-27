/* rolldown.c */
PRIVATE void rolldown_()
{
    Node temp, *node, *next;

    THREEPARAMS("rolldown");
    node = stk->next;
    next = node->next;
    temp = *next;
    if (OUTSIDE) {
	next->u = node->u;
	next->op = node->op;
	node->u = stk->u;
	node->op = stk->op;
	stk->u = temp.u;
	stk->op = temp.op;
	return;
    }
    temp = *stk;
    GTERNARY(node->op, node->u);
    GNULLARY(temp.op, temp.u);
    GNULLARY(next->op, next->u);
}
