/* rotate.c */
PRIVATE void rotate_()
{
    Node temp, *node, *next;

    THREEPARAMS("rotate");
    temp = *stk;
    node = stk->next;
    next = node->next;
    if (OUTSIDE) {
	stk->u = next->u;
	stk->op = next->op;
	next->u = temp.u;
	next->op = temp.op;
	return;
    }
    GTERNARY(temp.op, temp.u);
    GNULLARY(node->op, node->u);
    GNULLARY(next->op, next->u);
}
