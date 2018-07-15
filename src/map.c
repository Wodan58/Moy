/*
    module  : map.c
    version : 1.20
    date    : 07/15/18
*/
#ifndef MAP_X
#define MAP_C

#ifdef NEW_RUNTIME
void do_map(void)
{
    code_t *prog, *list, *root = 0, *cur;

    TRACE;
    prog = (code_t *)do_pop();
    for (list = (code_t *)do_pop(); list; list = list->next) {
	do_push(list->num);
	execute(prog);
	if (!root)
	    cur = root = joy_code();
	else
	    cur = cur->next = joy_code();
	cur->num = do_pop();
    }
    do_push((node_t)root);
}
#else
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
    if (new_version) {
	fprintf(outfp, "code_t *list, *root = 0, *cur;");
	fprintf(outfp, "for (list = (code_t *)do_pop(); list;");
	fprintf(outfp, "list = list->next) { do_push(list->num);");
	compile(prog);
	fprintf(outfp, "if (!root) cur = root = joy_code();");
	fprintf(outfp, "else cur = cur->next = joy_code();");
	fprintf(outfp, "cur->num = do_pop(); } do_push((node_t)root); }");
    } else {
	fprintf(outfp, "char *str, *ptr; ulong_t set, zet; int i = 0;");
	fprintf(outfp, "Node *cur, *save, temp, *root = 0, *last = 0;");
	fprintf(outfp, "cur = stk; POP(stk); switch (cur->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
	fprintf(outfp, "CONDITION; if ((save = stk) != 0) temp = *stk;");
	fprintf(outfp, "DUPLICATE(cur);");
	compile(prog);
	fprintf(outfp, "if (!root)");
	fprintf(outfp, "last = root = heapnode(stk->op, stk->u.ptr, 0); else ");
	fprintf(outfp, "last = last->next = heapnode(stk->op, stk->u.ptr, 0);");
	fprintf(outfp, "if ((stk = save) != 0) *stk = temp; RELEASE;");
	fprintf(outfp, "} PUSH(LIST_, root); break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "str = cur->u.str;");
	fprintf(outfp, "for (ptr = strdup(str); *str; str++) {");
	fprintf(outfp, "CONDITION; if ((save = stk) != 0) temp = *stk;");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
	compile(prog);
	fprintf(outfp, "ptr[i++] = stk->u.num;");
	fprintf(outfp, "if ((stk = save) != 0) *stk = temp; RELEASE;");
	fprintf(outfp, "} PUSH(STRING_, ptr); break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "set = cur->u.set;");
	fprintf(outfp, "for (zet = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "CONDITION; if ((save = stk) != 0) temp = *stk;");
	fprintf(outfp, "PUSH(INTEGER_, i);");
	compile(prog);
	fprintf(outfp, "zet |= 1 << stk->u.num;");
	fprintf(outfp, "if ((stk = save) != 0) *stk = temp; RELEASE;");
	fprintf(outfp, "} PUSH(SET_, zet); break; } }");
    }
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
		last = root = heapnode(stk->op, stk->u.ptr, 0);
	    else
		last = last->next = heapnode(stk->op, stk->u.ptr, 0);
	    if ((stk = save) != 0)
		*stk = temp;
	}
	PUSH(LIST_, root);
	break;
    case STRING_:
	str = cur->u.str;
	for (ptr = strdup(str); *str; str++) {
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
	    if (set & (1 << i)) {
		if ((save = stk) != 0)
		    temp = *stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		zet |= 1 << stk->u.num;
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
#endif
