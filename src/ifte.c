/*
    module  : ifte.c
    version : 1.17
    date    : 07/19/18
*/
#ifndef IFTE_X
#define IFTE_C

#ifdef NEW_RUNTIME
void do_ifte(void)
{
    code_t *prog[3];

    TRACE;
    prog[2] = (code_t *)do_pop();
    prog[1] = (code_t *)do_pop();
    prog[0] = (code_t *)do_pop();
    execute(prog[0]);
    execute(do_pop() ? prog[1] : prog[2]);
}
#else
#ifndef OLD_RUNTIME
int put_ifte(void)
{
    Node *prog[3];

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* IFTE */");
    if (!new_version)
	fprintf(outfp, "int num;");
    compile(prog[0]);
    if (new_version)
	fprintf(outfp, "if (do_pop()) {");
    else
	fprintf(outfp, "num = stk->u.num; POP(stk); if (num) {");
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
PRIVATE void do_ifte(void)
{
    Node *prog[3] /* , *save */;

#ifndef OLD_RUNTIME
    if (compiling && put_ifte())
	return;
    COMPILE;
#endif
    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
#if 0
    CONDITION;
    save = stk;
#endif
    exeterm(prog[0]);
    prog[0] = stk->u.num ? prog[1] : prog[2];
    POP(stk);
#if 0
    stk = save;
    RELEASE;
#endif
    exeterm(prog[0]);
}
#endif
#endif
