/*
    module  : while.c
    version : 1.14
    date    : 07/10/18
*/
#ifndef WHILE_X
#define WHILE_C

#ifdef RUNTIME
void do_while(void)
{
    code_t *prog[2];

    TRACE;
    prog[1] = (code_t *)do_pop();
    prog[0] = (code_t *)do_pop();
    for (;;) {
	execute(prog[0]);
	if (!do_pop())
	    break;
	execute(prog[1]);
    }
}
#else
#ifndef NCHECK
int put_while(void)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
#ifdef NEW_VERSION
    fprintf(outfp, "for (;;) { /* WHILE */");
    compile(prog[0]);
    fprintf(outfp, "if (!do_pop()) break;");
    compile(prog[1]);
    fprintf(outfp, "}");
#else
    fprintf(outfp, "{ /* WHILE */");
    fprintf(outfp, "int num; Node *save; for (;;) {");
    fprintf(outfp, "CONDITION; save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save; RELEASE;");
    fprintf(outfp, "if (!num) break;");
    compile(prog[1]);
    fprintf(outfp, "} }");
#endif
    return 1;
}
#endif

/**
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
PRIVATE void do_while(void)
{
    int num;
    Node *prog, *list, *save;

#ifndef NCHECK
    if (compiling && put_while())
	return;
    COMPILE;
#endif
    TWOPARAMS("while");
    TWOQUOTES("while");
    prog = stk->u.lis;
    POP(stk);
    list = stk->u.lis;
    POP(stk);
    for (;;) {
	CONDITION;
	save = stk;
	exeterm(list);
	num = stk->u.num;
	stk = save;
	RELEASE;
	if (!num)
	    break;
	exeterm(prog);
    }
}
#endif
#endif
