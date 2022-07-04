/*
    module  : map.c
    version : 1.25
    date    : 06/20/22
*/
#ifndef MAP_C
#define MAP_C

/**
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
#ifdef COMPILING
void put_map(pEnv env, Node *prog)
{
    fprintf(outfp, "{ /* MAP */");
    fprintf(outfp, "long set, zet; int i = 0;");
    fprintf(outfp, "char *str, *result, *volatile ptr;");
    fprintf(outfp, "Node *cur, *save, *root = 0, *last = 0;");
    fprintf(outfp, "cur = env->stk; POP(env->stk); switch (cur->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "DUPLICATE(cur);");
    compile(env, prog);
    fprintf(outfp, "if (!root)");
    fprintf(outfp, "last = root = newnode(env->stk->op, env->stk->u,0); else ");
    fprintf(outfp, "last = last->next = newnode(env->stk->op, env->stk->u,0);");
    fprintf(outfp, "env->stk = save;");
    fprintf(outfp, "} PUSH_PTR(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = GC_strdup(cur->u.str);");
    fprintf(outfp, "for (result = GC_strdup(str); *str; str++) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str);");
    compile(env, prog);
    fprintf(outfp, "result[i++] = env->stk->u.num;");
    fprintf(outfp, "env->stk = save;");
    fprintf(outfp, "} result[i] = 0; PUSH_PTR(STRING_, result); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = cur->u.set;");
    fprintf(outfp, "for (zet = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long)1 << i)) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "zet |= (long)1 << env->stk->u.num;");
    fprintf(outfp, "env->stk = save;");
    fprintf(outfp, "} PUSH_NUM(SET_, zet); break; } }");
}
#endif

PRIVATE void do_map(pEnv env)
{
    int i = 0;
    long set, zet;
    char *str, *result, *volatile ptr;
    Node *prog, *cur, *root = 0, *last = 0, *save;

    ONEPARAM("map");
    ONEQUOTE("map");
    prog = env->stk->u.lis;
    POP(env->stk);
    INSTANT(put_map);
    ONEPARAM("map");
    cur = env->stk;
    POP(env->stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next) {
	    save = env->stk;
	    DUPLICATE(cur);
	    exeterm(env, prog);
	    CHECKSTACK("map");
	    if (!root)
		last = root = newnode(env->stk->op, env->stk->u, 0);
	    else
		last = last->next = newnode(env->stk->op, env->stk->u, 0);
	    env->stk = save;
	}
	PUSH_PTR(LIST_, root);
	break;
    case STRING_:
	ptr = str = GC_strdup(cur->u.str);
	for (result = GC_strdup(str); *str; str++) {
	    save = env->stk;
	    PUSH_NUM(CHAR_, *str);
	    exeterm(env, prog);
	    result[i++] = env->stk->u.num;
	    env->stk = save;
	}
	result[i] = 0;
	PUSH_PTR(STRING_, result);
	break;
    case SET_:
	set = cur->u.set;
	for (zet = 0; i < SETSIZE_; i++)
	    if (set & ((long)1 << i)) {
		save = env->stk;
		PUSH_NUM(INTEGER_, i);
		exeterm(env, prog);
		zet |= (long)1 << env->stk->u.num;
		env->stk = save;
	    }
	PUSH_NUM(SET_, zet);
	break;
    default:
	BADAGGREGATE("map");
	break;
    }
}
#endif
