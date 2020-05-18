/*
    module  : split.c
    version : 1.22
    date    : 03/28/20
*/
#ifndef SPLIT_C
#define SPLIT_C

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
    fprintf(outfp, "unsigned i, yes = 0, no = 0;");
    fprintf(outfp, "char *str, *yes_str, *no_str;");
    fprintf(outfp, "ulong_t set, yes_set = 0, no_set = 0;");
    fprintf(outfp, "Node *save, *list, *root = 0, *cur, *head = 0, *tail;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "save = stk; DUPLICATE(list);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num) if (!root)");
    fprintf(outfp, "cur = root = newnode(list->op, list->u.ptr,0); else ");
    fprintf(outfp, "cur = cur->next = newnode(list->op, list->u.ptr, 0);");
    fprintf(outfp, "else if (!head)");
    fprintf(outfp, "tail = head = newnode(list->op,list->u.ptr,0); else ");
    fprintf(outfp, "tail = tail->next = newnode(list->op,list->u.ptr,0);");
    fprintf(outfp, "stk = save; }");
    fprintf(outfp, "PUSH(LIST_, root); PUSH(LIST_, head); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "yes_str = ck_strdup(str);");
    fprintf(outfp, "no_str = ck_strdup(str);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "yes_str[yes++] = *str;");
    fprintf(outfp, "else no_str[no++] = *str;");
    fprintf(outfp, "stk = save; }");
    fprintf(outfp, "yes_str[yes] = 0;");
    fprintf(outfp, "no_str[no] = 0;");
    fprintf(outfp, "PUSH(STRING_, yes_str);");
    fprintf(outfp, "PUSH(STRING_, no_str); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "PUSH(INTEGER_, i);");
    compile(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "yes_set |= (long_t)1 << i;");
    fprintf(outfp, "else no_set |= (long_t)1 << i;");
    fprintf(outfp, "stk = save; }");
    fprintf(outfp, "PUSH(SET_, yes_set);");
    fprintf(outfp, "PUSH(SET_, no_set); break; } }");
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
	    save = stk;
	    DUPLICATE(list);
	    exeterm(prog);
	    if (stk->u.num)
		if (!root)
		    cur = root = newnode(list->op, list->u.ptr, 0);
		else
		    cur = cur->next = newnode(list->op, list->u.ptr, 0);
	    else if (!head)
		tail = head = newnode(list->op, list->u.ptr, 0);
	    else
		tail = tail->next = newnode(list->op, list->u.ptr, 0);
	    stk = save;
	}
	PUSH(LIST_, root);
	PUSH(LIST_, head);
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	yesstring = ck_strdup(str);
	nostring = ck_strdup(str);
	for (; *str; str++) {
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    if (stk->u.num)
		yesstring[yesptr++] = *str;
	    else
		nostring[noptr++] = *str;
	    stk = save;
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
	    if (set & ((long_t)1 << i)) {
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		if (stk->u.num)
		    yes_set |= (long_t)1 << i;
		else
		    no_set |= (long_t)1 << i;
		stk = save;
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
