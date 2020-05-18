/*
    module  : filter.c
    version : 1.22
    date    : 03/28/20
*/
#ifndef FILTER_C
#define FILTER_C

#ifndef OLD_RUNTIME
int put_filter(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* FILTER */");
    fprintf(outfp, "int i = 0;");
    fprintf(outfp, "char *str, *ptr;");
    fprintf(outfp, "ulong_t set, zet = 0;");
    fprintf(outfp, "Node *save, *list, *root = 0, *cur;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "save = stk; DUPLICATE(list);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num) { if (!root)");
    fprintf(outfp, "cur = root = newnode(list->op, list->u.ptr,0); else ");
    fprintf(outfp, "cur = cur->next = newnode(list->op, list->u.ptr, 0);");
    fprintf(outfp, "} stk = save; }");
    fprintf(outfp, "PUSH(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "for (ptr = ck_strdup(str); *str; str++) {");
    fprintf(outfp, "save = stk; PUSH(CHAR_, (long_t)*str);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "ptr[i++] = *str;");
    fprintf(outfp, "stk = save; } ptr[i] = 0;");
    fprintf(outfp, "PUSH(STRING_, ptr); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "save = stk; PUSH(INTEGER_, i);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "zet |= (long_t)1 << i;");
    fprintf(outfp, "stk = save; }");
    fprintf(outfp, "PUSH(SET_, yes_set); break; } }");
    return 1;
}
#endif

/**
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
PRIVATE void do_filter(void)
{
    int i = 0;
    char *str, *ptr;
    ulong_t set, zet = 0;
    Node *prog, *save, *list, *root = 0, *cur;

#ifndef OLD_RUNTIME
    if (compiling && put_filter())
	return;
    COMPILE;
#endif
    TWOPARAMS("filter");
    ONEQUOTE("filter");
    prog = stk->u.lis;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	list = stk->u.lis;
	POP(stk);
	for (; list; list = list->next) {
	    save = stk;
	    DUPLICATE(list);
	    exeterm(prog);
	    if (stk->u.num) {
		if (!root)
		    cur = root = newnode(list->op, list->u.ptr, 0);
		else
		    cur = cur->next = newnode(list->op, list->u.ptr, 0);
	    }
	    stk = save;
	}
	PUSH(LIST_, root);
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	for (ptr = ck_strdup(str); *str; str++) {
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    if (stk->u.num)
		ptr[i++] = *str;
	    stk = save;
	}
	ptr[i] = 0;
	PUSH(STRING_, ptr);
	break;
    case SET_:
	set = stk->u.set;
	POP(stk);
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		if (stk->u.num)
		    zet |= (long_t)1 << i;
		stk = save;
	    }
	PUSH(SET_, zet);
	break;
    default:
	BADAGGREGATE("filter");
	break;
    }
}
#endif
