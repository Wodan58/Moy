/*
    module  : split.c
    version : 1.19
    date    : 07/15/18
*/
#ifndef SPLIT_X
#define SPLIT_C

#ifdef NEW_RUNTIME
void do_split(void)
{
    code_t *prog, *list, *root = 0, *cur, *head = 0, *tail;

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
	} else {
	    if (!head)
		tail = head = joy_code();
	    else
		tail = tail->next = joy_code();
	    tail->num = list->num;
	}
	(void)do_pop();
    }
    do_push((node_t)root);
    do_push((node_t)head);
}
#else
#ifndef OLD_RUNTIME
int put_split(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* SPLIT */");
    if (new_version) {
	fprintf(outfp, "code_t *list, *root = 0, *cur, *head = 0, *tail;");
	fprintf(outfp, "for (list = (code_t *)do_pop(); list;");
	fprintf(outfp, "list = list->next) { do_push(list->num);");
	compile(prog);
	fprintf(outfp, "if (do_pop()) { if (!root) cur = root = joy_code();");
	fprintf(outfp, "else cur = cur->next = joy_code(); cur->num =");
	fprintf(outfp, "list->num; } else { if (!head) tail = head =");
	fprintf(outfp, "joy_code(); else tail = tail->next = joy_code();");
	fprintf(outfp, "tail->num = list->num; } do_pop(); }");
	fprintf(outfp, "do_push((node_t)root); do_push((node_t)head); }");
    } else {
	fprintf(outfp, "unsigned i, yes = 0, no = 0;");
	fprintf(outfp, "char *str, *yes_str, *no_str;");
	fprintf(outfp, "ulong_t set, yes_set = 0, no_set = 0;");
	fprintf(outfp, "Node *save, *list, *root = 0, *cur, *head = 0, *tail;");
	fprintf(outfp, "switch (stk->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "list = stk->u.lis; POP(stk);");
	fprintf(outfp, "for (; list; list = list->next) {");
	fprintf(outfp, "CONDITION; save = stk; DUPLICATE(list);");
	compile(prog);
	fprintf(outfp, "if (stk->u.num) if (!root)");
	fprintf(outfp, "cur = root = heapnode(list->op, list->u.ptr,0); else ");
	fprintf(outfp, "cur = cur->next = heapnode(list->op, list->u.ptr, 0);");
	fprintf(outfp, "else if (!head)");
	fprintf(outfp, "tail = head = heapnode(list->op,list->u.ptr,0); else ");
	fprintf(outfp, "tail = tail->next = heapnode(list->op,list->u.ptr,0);");
	fprintf(outfp, "stk = save; RELEASE; }");
	fprintf(outfp, "PUSH(LIST_, root); PUSH(LIST_, head); break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "str = stk->u.str; POP(stk);");
	fprintf(outfp, "yes_str = strdup(str);");
	fprintf(outfp, "no_str = strdup(str);");
	fprintf(outfp, "for (; *str; str++) {");
	fprintf(outfp, "CONDITION; save = stk;");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
	compile(prog);
	fprintf(outfp, "if (stk->u.num)");
	fprintf(outfp, "yes_str[yes++] = *str;");
	fprintf(outfp, "else no_str[no++] = *str;");
	fprintf(outfp, "stk = save; RELEASE; }");
	fprintf(outfp, "yes_str[yes] = 0;");
	fprintf(outfp, "no_str[no] = 0;");
	fprintf(outfp, "PUSH(STRING_, yes_str);");
	fprintf(outfp, "PUSH(STRING_, no_str); break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "set = stk->u.set; POP(stk);");
	fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "CONDITION; save = stk;");
	fprintf(outfp, "PUSH(INTEGER_, i);");
	compile(prog);
	fprintf(outfp, "if (stk->u.num)");
	fprintf(outfp, "yes_set |= 1 << i;");
	fprintf(outfp, "else no_set |= 1 << i;");
	fprintf(outfp, "stk = save; RELEASE; }");
	fprintf(outfp, "PUSH(SET_, yes_set);");
	fprintf(outfp, "PUSH(SET_, no_set); break; } }");
    }
    return 1;
}
#endif

/**
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
PRIVATE void do_split(void)
{
    int i, yesptr = 0, noptr = 0;
    char *str, *yesstring, *nostring;
    ulong_t set, yes_set = 0, no_set = 0;
    Node *prog, *save, *list, *root = 0, *cur, *head = 0, *tail;

#ifndef OLD_RUNTIME
    if (compiling && put_split())
	return;
    COMPILE;
#endif
    TWOPARAMS("split");
    ONEQUOTE("split");
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
	    if (stk->u.num)
		if (!root)
		    cur = root = heapnode(list->op, list->u.ptr, 0);
		else
		    cur = cur->next = heapnode(list->op, list->u.ptr, 0);
	    else if (!head)
		tail = head = heapnode(list->op, list->u.ptr, 0);
	    else
		tail = tail->next = heapnode(list->op, list->u.ptr, 0);
	    stk = save;
	    RELEASE;
	}
	PUSH(LIST_, root);
	PUSH(LIST_, head);
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	yesstring = strdup(str);
	nostring = strdup(str);
	for (; str && *str; str++) {
	    CONDITION;
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    if (stk->u.num)
		yesstring[yesptr++] = *str;
	    else
		nostring[noptr++] = *str;
	    stk = save;
	    RELEASE;
	}
	yesstring[yesptr] = '\0';
	nostring[noptr] = '\0';
	PUSH(STRING_, yesstring);
	PUSH(STRING_, nostring);
	break;
    case SET_:
	set = stk->u.set;
	POP(stk);
	for (i = 0; i < SETSIZE_; i++) {
	    if (set & (1 << i)) {
		CONDITION;
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		if (stk->u.num)
		    yes_set |= 1 << i;
		else
		    no_set |= 1 << i;
		stk = save;
		RELEASE;
	    }
	}
	PUSH(SET_, yes_set);
	PUSH(SET_, no_set);
	break;
    default:
	BADAGGREGATE("split");
	break;
    }
}
#endif
#endif
