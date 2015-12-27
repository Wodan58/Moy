/* intern.c */
PRIVATE void intern_()
{
    char *ptr;

    ONEPARAM("intern");
    STRING("intern");
    strncpy(id, stk->u.str, ALEN);
    id[ALEN - 1] = 0;
    ptr = 0;
    if (id[0] == '-' || !strchr("(#)[]{}.;'\"0123456789", id[0]))
	for (ptr = id + 1; *ptr; ptr++)
	    if (!isalnum((int) *ptr) && !strchr("=_-", *ptr))
		break;
    if (!ptr || *ptr)
	execerror("valid name", id);
    HashValue(id);
    lookup();
    if (OUTSIDE) {
	if (location < firstlibra) {
	    stk->u.proc = location->u.proc;
	    stk->op = location - symtab;
	} else {
	    stk->u.ent = location;
	    stk->op = USR_;
	}
    } else if (location < firstlibra) {
	bucket.proc = location->u.proc;
	GUNARY(location - symtab, bucket);
    } else
	UNARY(USR_NEWNODE, location);
}
