/*
    module  : map.c
    version : 1.24
    date    : 03/15/21
*/
#ifndef MAP_C
#define MAP_C

#ifndef OLD_RUNTIME
int put_map(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* MAP */");
    fprintf(outfp, "ulong_t set, zet; int i = 0;");
    fprintf(outfp, "char *str, *result, *volatile ptr;");
    fprintf(outfp, "Node *cur, *save, temp, *root = 0, *last = 0;");
    fprintf(outfp, "cur = env->stk; POP(env->stk); switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
    fprintf(outfp, "if ((save = env->stk) != 0) temp = *env->stk;");
    fprintf(outfp, "DUPLICATE(cur);");
    compile(env, prog);
    fprintf(outfp, "if (!root)");
    fprintf(outfp, "last = root = newnode(env->stk->op, env->stk->u, 0); else ");
    fprintf(outfp, "last = last->next = newnode(env->stk->op, env->stk->u, 0);");
    fprintf(outfp, "if ((env->stk = save) != 0) *env->stk = temp;");
    fprintf(outfp, "} PUSH_PTR(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = GC_strdup(cur->u.str);");
    fprintf(outfp, "for (result = GC_strdup(str); *str; str++) {");
    fprintf(outfp, "if ((save = env->stk) != 0) temp = *env->stk;");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str);");
    compile(env, prog);
    fprintf(outfp, "result[i++] = env->stk->u.num;");
    fprintf(outfp, "if ((env->stk = save) != 0) *env->stk = temp;");
    fprintf(outfp, "} result[i] = 0; PUSH_PTR(STRING_, result); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = cur->u.set;");
    fprintf(outfp, "for (zet = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "if ((save = env->stk) != 0) temp = *env->stk;");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "zet |= (long_t)1 << env->stk->u.num;");
    fprintf(outfp, "if ((env->stk = save) != 0) *env->stk = temp;");
    fprintf(outfp, "} PUSH_NUM(SET_, zet); break; } }");
    return 1;
}
#endif

/**
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
PRIVATE void do_map(pEnv env)
{
    Node *prog, *cur, temp,
	 *root = 0, *last = 0, *save;
    int i = 0;
    ulong_t set, zet;
    char *str, *result, *volatile ptr;

#ifndef OLD_RUNTIME
    if (compiling && put_map(env))
	return;
    COMPILE;
#endif
    TWOPARAMS("map");
    ONEQUOTE("map");
    prog = env->stk->u.lis;
    POP(env->stk);
    cur = env->stk;
    POP(env->stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next) {
	    if ((save = env->stk) != 0)
		temp = *env->stk;
	    DUPLICATE(cur);
	    exeterm(env, prog);
#ifndef NCHECK
	    if (!env->stk)
		execerror("non-empty stack", "map");
#endif
	    if (!root)
		last = root = newnode(env->stk->op, env->stk->u, 0);
	    else
		last = last->next = newnode(env->stk->op, env->stk->u, 0);
	    if ((env->stk = save) != 0)
		*env->stk = temp;
	}
	PUSH_PTR(LIST_, root);
	break;
    case STRING_:
	ptr = str = GC_strdup(cur->u.str);
	for (result = GC_strdup(str); *str; str++) {
	    if ((save = env->stk) != 0)
		temp = *env->stk;
	    PUSH_NUM(CHAR_, *str);
	    exeterm(env, prog);
	    result[i++] = env->stk->u.num;
	    if ((env->stk = save) != 0)
		*env->stk = temp;
	}
	result[i] = 0;
	PUSH_PTR(STRING_, result);
	break;
    case SET_:
	set = cur->u.set;
	for (zet = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		if ((save = env->stk) != 0)
		    temp = *env->stk;
		PUSH_NUM(INTEGER_, i);
		exeterm(env, prog);
		zet |= (long_t)1 << env->stk->u.num;
		if ((env->stk = save) != 0)
		    *env->stk = temp;
	    }
	PUSH_NUM(SET_, zet);
	break;
    default:
	BADAGGREGATE("map");
	break;
    }
}
#endif
