/*
    module  : n_ary.c
    version : 1.5
    date    : 10/04/16
*/
/* n_ary.c */
PRIVATE void PROCEDURE(void)
{
    Node *prog, *top, *save;

    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
    prog = stk->u.lis;
    POP(stk);
    top = TOP;
#ifdef ARITY
    copy_(arity(prog));
#else
    CONDITION;
#endif
    exeterm(prog);
#ifdef RUNTIME_CHECKS
    if (!stk)
	execerror("value to push", NAME);
#endif
#ifndef ARITY
    RELEASE;
#endif
    save = stk;
    stk = top;
    DUPLICATE(save);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef TOP
