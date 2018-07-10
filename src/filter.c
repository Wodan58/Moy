/*
    module  : filter.c
    version : 1.18
    date    : 07/10/18
*/
#ifndef FILTER_X
#define FILTER_C

#ifdef RUNTIME
void do_filter(void)
{
    code_t *prog, *list, *root = 0, *cur;

    TRACE;
    prog = (code_t *)do_pop();
    for (list = (code_t *)do_pop(); list; list = list->next) {
	do_push(list->num);
	execute(prog);
	if (do_pop()) {
	    if (!root)
		cur = root = joy_code();
	    else
		cur = cur->next = joy_code();
	    cur->num = list->num;
	}
	(void)do_pop();
    }
    do_push((node_t)root);
}
#else
#ifndef NCHECK
int put_filter(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* FILTER */");
#ifdef NEW_VERSION
    fprintf(outfp, "code_t *list, *root = 0, *cur; TRACE;");
    fprintf(outfp, "for (list = (code_t *)do_pop(); list; list = list->next)");
    fprintf(outfp, "{ do_push(list->num);");
    compile(prog);
    fprintf(outfp, "if (do_pop()) {");
    fprintf(outfp, "if (!root)");
    fprintf(outfp, "cur = root = joy_code();");
    fprintf(outfp, "else ");
    fprintf(outfp, "cur = cur->next = joy_code();");
    fprintf(outfp, "cur->num = list->num;");
    fprintf(outfp, "} (void)do_pop(); }");
    fprintf(outfp, "do_push((node_t)root);");
#else
    fprintf(outfp, "int i = 0;");
    fprintf(outfp, "char *str, *ptr;");
    fprintf(outfp, "ulong_t set, zet = 0;");
    fprintf(outfp, "Node *save, *list, *root = 0, *cur;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "CONDITION; save = stk; DUPLICATE(list);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num) { if (!root)");
    fprintf(outfp, "cur = root = heapnode(list->op, list->u.ptr,0); else ");
    fprintf(outfp, "cur = cur->next = heapnode(list->op, list->u.ptr, 0);");
    fprintf(outfp, "} stk = save; RELEASE; }");
    fprintf(outfp, "PUSH(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "for (ptr = strdup(str); *str; str++) {");
    fprintf(outfp, "CONDITION; save = stk; PUSH(CHAR_, (long_t)*str);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "ptr[i++] = *str;");
    fprintf(outfp, "stk = save; RELEASE; } ptr[i] = 0;");
    fprintf(outfp, "PUSH(STRING_, ptr); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & (1 << i)) {");
    fprintf(outfp, "CONDITION; save = stk; PUSH(INTEGER_, i);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "zet |= 1 << i;");
    fprintf(outfp, "stk = save; RELEASE; }");
    fprintf(outfp, "PUSH(SET_, yes_set); break; } }");
#endif
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

#ifndef NCHECK
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
	    CONDITION;
	    save = stk;
	    DUPLICATE(list);
	    exeterm(prog);
	    if (stk->u.num) {
		if (!root)
		    cur = root = heapnode(list->op, list->u.ptr, 0);
		else
		    cur = cur->next = heapnode(list->op, list->u.ptr, 0);
	    }
	    stk = save;
	    RELEASE;
	}
	PUSH(LIST_, root);
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	for (ptr = strdup(str); *str; str++) {
	    CONDITION;
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    if (stk->u.num)
		ptr[i++] = *str;
	    stk = save;
	    RELEASE;
	}
	ptr[i] = 0;
	PUSH(STRING_, ptr);
	break;
    case SET_:
	set = stk->u.set;
	POP(stk);
	for (i = 0; i < SETSIZE_; i++)
	    if (set & (1 << i)) {
		CONDITION;
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		if (stk->u.num)
		    zet |= 1 << i;
		stk = save;
		RELEASE;
	    }
	PUSH(SET_, zet);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("filter");
#endif
    }
}
#endif
#endif
