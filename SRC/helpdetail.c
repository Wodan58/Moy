/* helpdetail.c */
PRIVATE void helpdetail_()
{
    Node *n;

    ONEPARAM("HELP");
    LIST("HELP");
    printf("\n");
    n = stk->u.lis;
    while (n) {
	if (n->op == USR_) {
	    printf("%s  ==\n    ", n->u.ent->name);
	    writeterm(n->u.ent->u.body, stdout);
	    printf("\n");
	    break;
	} else {
	    int op;
	    if ((op = n->op) == BOOLEAN_)
		op = n->u.num ? TRUE_ : FALSE_;
	    if (op == INTEGER_ && n->u.num == MAXINT)
		op = MAXINT_;
	    printf("%s  :  %s.\n%s\n", optable[op].name,
		   optable[op].messg1, optable[op].messg2);
	}
	printf("\n");
	n = n->next;
    }
    POP(stk);
}
