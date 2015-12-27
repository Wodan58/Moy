/* n_ary.c */
PRIVATE void PROCEDURE()
{
    Node *save, *top, *node;

    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
    save = stk;
    POP(stk);
    top = TOP;

    inside_condition++;
    exeterm(save->u.lis);
    if (!stk)
	execerror("value to push", NAME);
    node = stk;
    inside_condition--;

    stk = top;
    DUPLICATE(node);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef TOP
