/* fread.c */
PRIVATE void fread_()
{
    int i;
    size_t count;
    Node *cur = 0;
    unsigned char *buf;

    TWOPARAMS("fread");
    INTEGER("fread");
    count = stk->u.num;
    POP(stk);
    FILE("fread");
    buf = GC_malloc(count);
    for (i = fread(buf, 1, count, stk->u.fil) - 1; i >= 0; i--)
	cur = newnode(INTEGER_, (Types) buf[i], cur);
    PUSH(LIST_, cur);
}
