/*
    module  : nary.h
    version : 1.8
    date    : 10/23/17
*/
#ifndef NCHECK
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    int arr;
    Node *prog;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* %s */", NAME);
    fprintf(outfp, "Node temp, *top = %s;", TOPSTR);
    if ((arr = arity(prog)) != ARITY)
	fprintf(outfp, "CONDITION;");
    evaluate(prog);
    fprintf(outfp, "temp = *stk;");
    if (arr != ARITY)
	fprintf(outfp, "RELEASE;");
    fprintf(outfp, "stk = top; DUPLICATE(&temp); }");
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    Node *prog, *top, temp;

#ifndef NCHECK
    if (optimizing && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
#endif
    prog = stk->u.lis;
    POP(stk);
    top = TOP;
    CONDITION;
    exeterm(prog);
#ifndef NCHECK
    if (stk == memory)
	execerror("value to push", NAME);
#endif
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
