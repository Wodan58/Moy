/*
    module  : map.c
    version : 1.23
    date    : 03/28/20
*/
#ifndef MAP_C
#define MAP_C

#ifndef OLD_RUNTIME
int put_map(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* MAP */");
    fprintf(outfp, "char *str, *ptr; ulong_t set, zet; int i = 0;");
    fprintf(outfp, "Node *cur, *save, temp, *root = 0, *last = 0;");
    fprintf(outfp, "cur = stk; POP(stk); switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
    fprintf(outfp, "if ((save = stk) != 0) temp = *stk;");
    fprintf(outfp, "DUPLICATE(cur);");
    compile(prog);
    fprintf(outfp, "if (!root)");
    fprintf(outfp, "last = root = newnode(stk->op, stk->u.ptr, 0); else ");
    fprintf(outfp, "last = last->next = newnode(stk->op, stk->u.ptr, 0);");
    fprintf(outfp, "if ((stk = save) != 0) *stk = temp;");
    fprintf(outfp, "} PUSH(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = cur->u.str;");
    fprintf(outfp, "for (ptr = ck_strdup(str); *str; str++) {");
    fprintf(outfp, "if ((save = stk) != 0) temp = *stk;");
    fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
    compile(prog);
    fprintf(outfp, "ptr[i++] = stk->u.num;");
    fprintf(outfp, "if ((stk = save) != 0) *stk = temp;");
    fprintf(outfp, "} PUSH(STRING_, ptr); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = cur->u.set;");
    fprintf(outfp, "for (zet = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "if ((save = stk) != 0) temp = *stk;");
    fprintf(outfp, "PUSH(INTEGER_, i);");
    compile(prog);
    fprintf(outfp, "zet |= (long_t)1 << stk->u.num;");
    fprintf(outfp, "if ((stk = save) != 0) *stk = temp;");
    fprintf(outfp, "} PUSH(SET_, zet); break; } }");
    return 1;
}
#endif

/**
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
PRIVATE void do_map(void)
{
    Node *prog, *cur, temp,
	 *root = 0, *last = 0, *save;
    int i = 0;
    char *str, *ptr;
    ulong_t set, zet;

#ifndef OLD_RUNTIME
    if (compiling && put_map())
	return;
    COMPILE;
#endif
    TWOPARAMS("map");
    ONEQUOTE("map");
    prog = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next) {
	    if ((save = stk) != 0)
		temp = *stk;
	    DUPLICATE(cur);
	    exeterm(prog);
#ifndef NCHECK
	    if (!stk)
		execerror("non-empty stack", "map");
#endif
	    if (!root)
		last = root = newnode(stk->op, stk->u.ptr, 0);
	    else
		last = last->next = newnode(stk->op, stk->u.ptr, 0);
	    if ((stk = save) != 0)
		*stk = temp;
	}
	PUSH(LIST_, root);
	break;
    case STRING_:
	str = cur->u.str;
	for (ptr = ck_strdup(str); *str; str++) {
	    if ((save = stk) != 0)
		temp = *stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    ptr[i++] = stk->u.num;
	    if ((stk = save) != 0)
		*stk = temp;
	}
	ptr[i] = 0;
	PUSH(STRING_, ptr);
	break;
    case SET_:
	set = cur->u.set;
	for (zet = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		if ((save = stk) != 0)
		    temp = *stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		zet |= (long_t)1 << stk->u.num;
		if ((stk = save) != 0)
		    *stk = temp;
	    }
	PUSH(SET_, zet);
	break;
    default:
	BADAGGREGATE("map");
	break;
    }
}
#endif
