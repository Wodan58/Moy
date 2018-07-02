/*
    module  : while.c
    version : 1.12
    date    : 07/02/18
*/

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
    fprintf(outfp, "{ /* WHILE */");
    fprintf(outfp, "int num; Node *save; for (;;) {");
    fprintf(outfp, "CONDITION;");
    fprintf(outfp, "save = stk;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "if (!num) break;");
    compile(prog[1]);
    fprintf(outfp, "} }");
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
