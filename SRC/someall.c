/*
    module  : someall.c
    version : 1.11
    date    : 04/22/17
*/
#ifndef NCHECK
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    void *save;
    Node *prog;
    unsigned op, op1;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    if ((op = pop_history(&op1)) == LIST_) {
	fprintf(outfp, "{ /* SOMEALL-LIST */");
	fprintf(outfp, "unsigned num = %d;", INITIAL);
	fprintf(outfp, "Node *list, *save;");
	fprintf(outfp, "assert(stk->op == LIST_);");
	fprintf(outfp, "list = stk->u.lis; POP(stk);");
	fprintf(outfp, "for (; list; list = list->next) {");
	fprintf(outfp, "CONDITION; save = stk; DUPLICATE(list);");
	evaluate(prog);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num != %d) break; }", INITIAL);
    } else if (op == STRING_) {
	fprintf(outfp, "{ /* SOMEALL-STRING */");
	fprintf(outfp, "unsigned num = %d;", INITIAL);
	fprintf(outfp, "Node *save;");
	fprintf(outfp, "assert(stk->op == STRING_);");
	fprintf(outfp, "char *str = stk->u.str; POP(stk);");
	fprintf(outfp, "for (; *str; str++) {");
	fprintf(outfp, "CONDITION; save = stk; PUSH(CHAR_, (long_t)*str);");
	evaluate(prog);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num != %d) break; }", INITIAL);
    } else if (op == SET_) {
	fprintf(outfp, "{ /* SOMEALL-SET */");
	fprintf(outfp, "unsigned i, num = %d;", INITIAL);
	fprintf(outfp, "Node *save; ulong_t set;");
	fprintf(outfp, "assert(stk->op == SET_);");
	fprintf(outfp, "set = stk->u.set; POP(stk);");
	fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "CONDITION; save = stk; PUSH(INTEGER_, i);");
	evaluate(prog);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num != %d) break; }", INITIAL);
    } else {
	fprintf(outfp, "{ /* SOMEALL-GENERIC */");
	fprintf(outfp, "unsigned i, num = %d;", INITIAL);
	fprintf(outfp, "char *str;");
	fprintf(outfp, "ulong_t set;");
	fprintf(outfp, "Node *list, *save;");
	fprintf(outfp, "switch (stk->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "list = stk->u.lis; POP(stk);");
	fprintf(outfp, "for (; list; list = list->next) {");
	fprintf(outfp, "CONDITION; save = stk; DUPLICATE(list);");
	save = new_history();
	add_history(INTEGER_);
	evaluate(prog);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "str = stk->u.str; POP(stk);");
	fprintf(outfp, "for (; *str; str++) {");
	fprintf(outfp, "CONDITION; save = stk; PUSH(CHAR_, (long_t)*str);");
	old_history(save);
	add_history(CHAR_);
	evaluate(prog);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "set = stk->u.set; POP(stk);");
	fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "CONDITION; save = stk; PUSH(INTEGER_, i);");
	old_history(save);
	add_history(INTEGER_);
	evaluate(prog);
	fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
	fprintf(outfp, "if (num != %d) break; } break; }", INITIAL);
    }
    fprintf(outfp, "PUSH(BOOLEAN_, num); }");
    add_history(BOOLEAN_);
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
