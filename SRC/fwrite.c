/* fwrite.c */
PRIVATE void fwrite_()
{
    int i;
    Node *n;
    size_t length;
    unsigned char *buf;

    TWOPARAMS("fwrite");
    LIST("fwrite");
    for (n = stk->u.lis, length = 0; n; n = n->next, length++)
	if (n->op != INTEGER_)
	    execerror("numeric list", "fwrite");
    buf = GC_malloc(length);
    for (n = stk->u.lis, i = 0; n; n = n->next, i++)
	buf[i] = n->u.num;
    POP(stk);
    FILE("fwrite");
    fwrite(buf, length, 1, stk->u.fil);
}
