/*
    module  : filter.c
    version : 1.24
    date    : 06/20/22
*/
#ifndef FILTER_C
#define FILTER_C

/**
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
#ifdef COMPILING
void put_filter(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* FILTER */");
    fprintf(outfp, "int i = 0;");
    fprintf(outfp, "long set, zet = 0;");
    fprintf(outfp, "char *str, *result, *volatile ptr;");
    fprintf(outfp, "Node *save, *list, *root = 0, *cur;");
    fprintf(outfp, "switch (env->stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = env->stk->u.lis; POP(env->stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "save = env->stk; DUPLICATE(list);");
    compile(env, prog);
    fprintf(outfp, "if (env->stk->u.num) { if (!root)");
    fprintf(outfp, "cur = root = newnode(list->op, list->u, 0); else ");
    fprintf(outfp, "cur = cur->next = newnode(list->op, list->u, 0);");
    fprintf(outfp, "} env->stk = save; }");
    fprintf(outfp, "PUSH_PTR(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = GC_strdup(env->stk->u.str); POP(env->stk);");
    fprintf(outfp, "for (result = GC_strdup(str); *str; str++) {");
    fprintf(outfp, "save = env->stk; PUSH_NUM(CHAR_, *str);");
    compile(env, prog);
    fprintf(outfp, "if (env->stk->u.num)");
    fprintf(outfp, "result[i++] = *str;");
    fprintf(outfp, "env->stk = save; } result[i] = 0;");
    fprintf(outfp, "PUSH_PTR(STRING_, result); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = env->stk->u.set; POP(env->stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long)1 << i)) {");
    fprintf(outfp, "save = env->stk; PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "if (env->stk->u.num)");
    fprintf(outfp, "zet |= (long)1 << i;");
    fprintf(outfp, "env->stk = save; }");
    fprintf(outfp, "PUSH_NUM(SET_, zet); break; } }");
}
#endif

PRIVATE void do_filter(pEnv env)
{
    int i = 0;
    long set, zet = 0;
    char *str, *result, *volatile ptr;
    Node *prog, *save, *list, *root = 0, *cur;

    ONEPARAM("filter");
    ONEQUOTE("filter");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_filter);
    ONEPARAM("filter");
    switch (env->stk->op) {
    case LIST_:
	list = env->stk->u.lis;
	POP(env->stk);
	for (; list; list = list->next) {
	    save = env->stk;
	    DUPLICATE(list);
	    exeterm(env, prog);
	    if (env->stk->u.num) {
		if (!root)
		    cur = root = newnode(list->op, list->u, 0);
		else
		    cur = cur->next = newnode(list->op, list->u, 0);
	    }
	    env->stk = save;
	}
	PUSH_PTR(LIST_, root);
	break;
    case STRING_:
	ptr = str = GC_strdup(env->stk->u.str);
	POP(env->stk);
	for (result = GC_strdup(str); *str; str++) {
	    save = env->stk;
	    PUSH_NUM(CHAR_, *str);
	    exeterm(env, prog);
	    if (env->stk->u.num)
		result[i++] = *str;
	    env->stk = save;
	}
	result[i] = 0;
	PUSH_PTR(STRING_, result);
	break;
    case SET_:
	set = env->stk->u.set;
	POP(env->stk);
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long)1 << i)) {
		save = env->stk;
		PUSH_NUM(INTEGER_, i);
		exeterm(env, prog);
		if (env->stk->u.num)
		    zet |= (long)1 << i;
		env->stk = save;
	    }
	PUSH_NUM(SET_, zet);
	break;
    default:
	BADAGGREGATE("filter");
	break;
    }
}
#endif
