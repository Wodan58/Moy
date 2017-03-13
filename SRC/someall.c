/*
    module  : someall.c
    version : 1.9
    date    : 03/12/17
*/
#ifndef NCHECK
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    Node *prog;

    if (stk->op != LIST_)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* SOMEALL */");
    fprintf(outfp, "char *str;");
    fprintf(outfp, "ulong_t set;");
    fprintf(outfp, "unsigned i, num = %d;", INITIAL);
    fprintf(outfp, "Node *list, *save;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "CONDITION; save = stk; DUPLICATE(list);");
    evaluate(prog);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "CONDITION; save = stk; PUSH(CHAR_, (long_t)*str);");
    evaluate(prog);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & (1 << i)) {");
    fprintf(outfp, "CONDITION; save = stk; PUSH(INTEGER_, i);");
    evaluate(prog);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "} PUSH(BOOLEAN_, num); }");
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
    if (optimizing && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
    TWOPARAMS(NAME);
    ONEQUOTE(NAME);
#endif
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
