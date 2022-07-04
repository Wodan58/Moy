/*
    module  : split.c
    version : 1.24
    date    : 06/20/22
*/
#ifndef SPLIT_C
#define SPLIT_C

/**
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
#ifdef COMPILING
void put_split(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* SPLIT */");
    fprintf(outfp, "unsigned i, yes = 0, no = 0;");
    fprintf(outfp, "long set, yes_set = 0, no_set = 0;");
    fprintf(outfp, "char *str, *yes_str, *no_str, *volatile ptr;");
    fprintf(outfp, "Node *save, *list, *root = 0, *cur, *head = 0, *tail;");
    fprintf(outfp, "switch (env->stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = env->stk->u.lis; POP(env->stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "save = env->stk; DUPLICATE(list);");
    compile(env, prog);
    fprintf(outfp, "if (env->stk->u.num) if (!root)");
    fprintf(outfp, "cur = root = newnode(list->op, list->u, 0); else ");
    fprintf(outfp, "cur = cur->next = newnode(list->op, list->u, 0);");
    fprintf(outfp, "else if (!head)");
    fprintf(outfp, "tail = head = newnode(list->op,list->u, 0); else ");
    fprintf(outfp, "tail = tail->next = newnode(list->op, list->u, 0);");
    fprintf(outfp, "env->stk = save; }");
    fprintf(outfp, "PUSH_PTR(LIST_, root); PUSH_PTR(LIST_, head); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = GC_strdup(env->stk->u.str); POP(env->stk);");
    fprintf(outfp, "yes_str = GC_strdup(str);");
    fprintf(outfp, "no_str = GC_strdup(str);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str);");
    compile(env, prog);
    fprintf(outfp, "if (env->stk->u.num)");
    fprintf(outfp, "yes_str[yes++] = *str;");
    fprintf(outfp, "else no_str[no++] = *str;");
    fprintf(outfp, "env->stk = save; }");
    fprintf(outfp, "yes_str[yes] = 0;");
    fprintf(outfp, "no_str[no] = 0;");
    fprintf(outfp, "PUSH_PTR(STRING_, yes_str);");
    fprintf(outfp, "PUSH_PTR(STRING_, no_str); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = env->stk->u.set; POP(env->stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long)1 << i)) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "if (env->stk->u.num)");
    fprintf(outfp, "yes_set |= (long)1 << i;");
    fprintf(outfp, "else no_set |= (long)1 << i;");
    fprintf(outfp, "env->stk = save; }");
    fprintf(outfp, "PUSH_NUM(SET_, yes_set);");
    fprintf(outfp, "PUSH_NUM(SET_, no_set); break; } }");
}
#endif

PRIVATE void do_split(pEnv env)
{
    int i, yesptr = 0, noptr = 0;
    long set, yes_set = 0, no_set = 0;
    char *str, *yesstring, *nostring, *volatile ptr;
    Node *prog, *save, *list, *root = 0, *cur, *head = 0, *tail;

    ONEPARAM("split");
    ONEQUOTE("split");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_split);
    ONEPARAM("split");
    switch (env->stk->op) {
    case LIST_:
	list = env->stk->u.lis;
	POP(env->stk);
	for (; list; list = list->next) {
	    save = env->stk;
	    DUPLICATE(list);
	    exeterm(env, prog);
	    if (env->stk->u.num)
		if (!root)
		    cur = root = newnode(list->op, list->u, 0);
		else
		    cur = cur->next = newnode(list->op, list->u, 0);
	    else if (!head)
		tail = head = newnode(list->op, list->u, 0);
	    else
		tail = tail->next = newnode(list->op, list->u, 0);
	    env->stk = save;
	}
	PUSH_PTR(LIST_, root);
	PUSH_PTR(LIST_, head);
	break;
    case STRING_:
	ptr = str = GC_strdup(env->stk->u.str);
	POP(env->stk);
	yesstring = GC_strdup(str);
	nostring = GC_strdup(str);
	for (; *str; str++) {
	    save = env->stk;
	    PUSH_NUM(CHAR_, *str);
	    exeterm(env, prog);
	    if (env->stk->u.num)
		yesstring[yesptr++] = *str;
	    else
		nostring[noptr++] = *str;
	    env->stk = save;
	}
	yesstring[yesptr] = '\0';
	nostring[noptr] = '\0';
	PUSH_PTR(STRING_, yesstring);
	PUSH_PTR(STRING_, nostring);
	break;
    case SET_:
	set = env->stk->u.set;
	POP(env->stk);
	for (i = 0; i < SETSIZE_; i++) {
	    if (set & ((long)1 << i)) {
		save = env->stk;
		PUSH_NUM(INTEGER_, i);
		exeterm(env, prog);
		if (env->stk->u.num)
		    yes_set |= (long)1 << i;
		else
		    no_set |= (long)1 << i;
		env->stk = save;
	    }
	}
	PUSH_NUM(SET_, yes_set);
	PUSH_NUM(SET_, no_set);
	break;
    default:
	BADAGGREGATE("split");
	break;
    }
}
#endif
