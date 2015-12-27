/* rollup.c */
PRIVATE void rollup_()
{
    Node temp, *node, *next;

    THREEPARAMS("rollup");
    temp = *stk;
    node = stk->next;
    next = node->next;
    if (OUTSIDE) {
	stk->u = node->u;
	stk->op = node->op;
	node->u = next->u;
	node->op = next->op;
	next->u = temp.u;
	next->op = temp.op;
	return;
    }
    GTERNARY(temp.op, temp.u);
    GNULLARY(next->op, next->u);
    GNULLARY(node->op, node->u);
}
