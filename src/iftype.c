/*
    module  : iftype.c
    version : 1.4
    date    : 04/15/17
*/
#ifndef NCHECK
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    void *save;
    Node *prog[2];

    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "if (stk->op == %d) {", TYP);
    fprintf(outfp, "/* IFTYPE */");
    save = new_history();
    evaluate(prog[0]);
    old_history(save);
    fprintf(outfp, "} else {");
    evaluate(prog[1]);
    fprintf(outfp, "}");
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    Node *first, *second;

#ifndef NCHECK
    if (optimizing && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
    TWOPARAMS(NAME);
    TWOQUOTES(NAME);
#endif
    second = stk->u.lis;
    POP(stk);
    first = stk->u.lis;
    POP(stk);
    exeterm(stk->op == TYP ? first : second);
}

#undef PROCEDURE
#undef NAME
#undef TYP
#undef CAT
#undef PUT_PROC
