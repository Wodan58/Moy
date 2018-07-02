/*
    module  : nary.h
    version : 1.10
    date    : 07/02/18
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
    fprintf(outfp, "{ /* %s */", NAME);
    fprintf(outfp, "Node temp, *top = %s;", TOPSTR);
    fprintf(outfp, "CONDITION;");
    compile(prog);
    fprintf(outfp, "temp = *stk;");
    fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&temp); }");
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    Node *prog, *top, temp;

#ifndef NCHECK
    if (compiling && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
#endif
    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
    prog = stk->u.lis;
    POP(stk);
    top = TOP;
    CONDITION;
    exeterm(prog);
    if (!stk)
	execerror("value to push", NAME);
    temp = *stk;
    RELEASE;
    stk = top;
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef TOP
#undef TOPSTR
#undef ARITY
#undef CAT
#undef PUT_PROC
