/*
    module  : n_ary.c
    version : 1.2
    date    : 05/06/16
*/
/* n_ary.c */
PRIVATE void PROCEDURE(void)
{
    Node *save, *top;

    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
    save = stk;
    POP(stk);
    top = TOP;
    inside_condition++;
    exeterm(save->u.lis);
    inside_condition--;
#ifdef RUNTIME_CHECKS
    if (!stk)
	execerror("value to push", NAME);
#endif
    save = stk;
    stk = top;
    DUPLICATE(save);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef TOP
