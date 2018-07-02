/*
    module  : iftype.h
    version : 1.5
    date    : 07/02/18
*/
#ifndef NCHECK
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    Node *prog[2];

    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "if (stk->op == %d) {", TYP);
    fprintf(outfp, "/* IFTYPE */");
    compile(prog[0]);
    fprintf(outfp, "} else {");
    compile(prog[1]);
    fprintf(outfp, "}");
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    Node *first, *second;

#ifndef NCHECK
    if (compiling && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
#endif
    TWOPARAMS(NAME);
    TWOQUOTES(NAME);
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
