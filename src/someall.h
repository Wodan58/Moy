/*
    module  : someall.h
    version : 1.19
    date    : 03/15/21
*/
#ifndef OLD_RUNTIME
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)

int PUT_PROC(PROCEDURE)(pEnv env)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = env->stk->u.lis;
    POP(env->stk);
    printstack(env, outfp);
    fprintf(outfp, "{ /* SOMEALL */");
    fprintf(outfp, "ulong_t set;");
    fprintf(outfp, "char *str, *volatile ptr;");
    fprintf(outfp, "unsigned i, num = %d;", INITIAL);
    fprintf(outfp, "Node *list, *save;");
    fprintf(outfp, "switch (env->stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = env->stk->u.lis; POP(env->stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "DUPLICATE(list);");
    compile(env, prog);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "ptr = str = GC_strdup(env->stk->u.str); POP(env->stk);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "PUSH_NUM(CHAR_, *str);");
    compile(env, prog);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = env->stk->u.set; POP(env->stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "save = env->stk;");
    fprintf(outfp, "PUSH_NUM(INTEGER_, i);");
    compile(env, prog);
    fprintf(outfp, "num = env->stk->u.num; env->stk = save;");
    fprintf(outfp, "if (num != %d) break; } break; }", INITIAL);
    fprintf(outfp, "PUSH_NUM(BOOLEAN_, num); }");
    return 1;
}
#endif

PRIVATE void PROCEDURE(pEnv env)
{
    ulong_t set;
    int i, num = INITIAL;
    char *str, *volatile ptr;
    Node *prog, *list, *save;

#ifndef OLD_RUNTIME
    if (compiling && PUT_PROC(PROCEDURE)(env))
	return;
    COMPILE;
#endif
    TWOPARAMS(NAME);
    ONEQUOTE(NAME);
    prog = env->stk->u.lis;
    POP(env->stk);
    switch (env->stk->op) {
    case LIST_:
	list = env->stk->u.lis;
	POP(env->stk);
	for (; list; list = list->next) {
	    save = env->stk;
	    DUPLICATE(list);
	    exeterm(env, prog);
	    num = env->stk->u.num;
	    env->stk = save;
	    if (num != INITIAL)
		break;
	}
	break;
    case STRING_:
	ptr = str = GC_strdup(env->stk->u.str);
	POP(env->stk);
	for (; *str; str++) {
	    save = env->stk;
	    PUSH_NUM(CHAR_, *str);
	    exeterm(env, prog);
	    num = env->stk->u.num;
	    env->stk = save;
	    if (num != INITIAL)
		break;
	}
	break;
    case SET_:
	set = env->stk->u.set;
	POP(env->stk);
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		save = env->stk;
		PUSH_NUM(INTEGER_, i);
		exeterm(env, prog);
		num = env->stk->u.num;
		env->stk = save;
		if (num != INITIAL)
		    break;
	    }
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
    PUSH_NUM(BOOLEAN_, num);
}

#undef PROCEDURE
#undef NAME
#undef INITIAL
#undef CAT
#undef PUT_PROC
