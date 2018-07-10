/*
    module  : someall.h
    version : 1.16
    date    : 07/10/18
*/
#ifndef NCHECK
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
#ifdef NEW_VERSION
#ifdef SOME
    fprintf(outfp, "{ /* SOME */");
    fprintf(outfp, "int num = 0; code_t *list; TRACE;");
    fprintf(outfp, "for (list = (code_t *)do_pop(); list;");
    fprintf(outfp, "list = list->next) { do_push(list->num);");
    compile(prog);
    fprintf(outfp, "num = do_pop(); do_pop(); if (num) break;");
#else
    fprintf(outfp, "{ /* ALL */");
    fprintf(outfp, "int num = 1; code_t *list; TRACE;");
    fprintf(outfp, "for (list = (code_t *)do_pop(); list;");
    fprintf(outfp, "list = list->next) { do_push(list->num);");
    compile(prog);
    fprintf(outfp, "num = do_pop(); do_pop(); if (!num) break;");
#endif
    fprintf(outfp, "} do_push(num); }");
#else
    fprintf(outfp, "{ /* SOMEALL */");
    fprintf(outfp, "unsigned i, num = %d;", INITIAL);
    fprintf(outfp, "char *str;");
    fprintf(outfp, "ulong_t set;");
    fprintf(outfp, "Node *list, *save;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "DUPLICATE(list);");
    compile(prog);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
    compile(prog);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & (1 << i)) {");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "PUSH(INTEGER_, i);");
    compile(prog);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (num != %d) break; } break; }", INITIAL);
    fprintf(outfp, "PUSH(BOOLEAN_, num); }");
#endif
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    char *str;
    ulong_t set;
    int i, num = INITIAL;
    Node *prog, *list, *save;

#ifndef NCHECK
    if (compiling && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
#endif
    TWOPARAMS(NAME);
    ONEQUOTE(NAME);
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
	    num = stk->u.num;
	    stk = save;
	    RELEASE;
	    if (num != INITIAL)
		break;
	}
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	for (; str && *str; str++) {
	    CONDITION;
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    num = stk->u.num;
	    stk = save;
	    RELEASE;
	    if (num != INITIAL)
		break;
	}
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
		num = stk->u.num;
		stk = save;
		RELEASE;
		if (num != INITIAL)
		    break;
	    }
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE(NAME);
#endif
    }
    PUSH(BOOLEAN_, num);
}

#undef PROCEDURE
#undef NAME
#undef INITIAL
#undef CAT
#undef PUT_PROC
