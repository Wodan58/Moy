/*
    module  : primrec.c
    version : 1.11
    date    : 07/15/18
*/
#ifndef PRIMREC_X
#define PRIMREC_C

#ifdef NEW_RUNTIME
void do_primrec(void)
{
    int i, num;
    code_t *prog, *init;

    TRACE;
    prog = (code_t *)do_pop();
    init = (code_t *)do_pop();
    for (i = num = do_pop(); i; i--)
	do_push(i);
    execute(init);
    while (num--)
	execute(prog);
}
#else
#ifndef OLD_RUNTIME
int put_primrec(void)
{
    Node *prog, *init;

    if (!(LIST_1 && LIST_2))
	return 0;
    prog = stk->u.lis;
    POP(stk);
    init = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* PRIMREC */");
    if (new_version) {
	fprintf(outfp, "int i, num; code_t *prog, *init;");
	fprintf(outfp, "for (i = num = do_pop(); i; i--) do_push(i);");
    } else {
	fprintf(outfp, "int i, num = 0; Node *cur;");
	fprintf(outfp, "char *str; ulong_t set;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "switch (cur->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next, num++)");
	fprintf(outfp, "DUPLICATE(cur); break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "for (num = strlen(str = cur->u.str); *str; str++)");
	fprintf(outfp, "PUSH(CHAR_, (long_t)*str); break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "set = cur->u.set;");
	fprintf(outfp, "for (num = i = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "PUSH(INTEGER_, i); num++; } break;");
	fprintf(outfp, "case INTEGER_:");
	fprintf(outfp, "for (num = i = cur->u.num; i; i--)");
	fprintf(outfp, "PUSH(INTEGER_, i); break; }");
    }
    compile(init);
    fprintf(outfp, "while (num--) {");
    compile(prog);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
PRIVATE void do_primrec(void)
{
    char *str;
    long_t set;
    int i, num = 0;
    Node *prog, *init, *cur;

#ifndef OLD_RUNTIME
    if (compiling && put_primrec())
	return;
    COMPILE;
#endif
    THREEPARAMS("primrec");
    prog = stk->u.lis;
    POP(stk);
    init = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next, num++)
	    DUPLICATE(cur);
	break;
    case STRING_:
	for (num = strlen(str = cur->u.str); *str; str++)
	    PUSH(CHAR_, (long_t)*str);
	break;
    case SET_:
	set = cur->u.set;
	for (i = 0; i < SETSIZE_; i++)
	    if (set & (1 << i)) {
		PUSH(INTEGER_, i);
		num++;
	    }
	break;
    case INTEGER_:
	for (i = num = cur->u.num; i; i--)
	    PUSH(INTEGER_, i);
	break;
    default:
	BADDATA("primrec");
	break;
    }
    exeterm(init);
    while (num--)
	exeterm(prog);
}
#endif
#endif
