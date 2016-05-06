/*
    module  : if_type.c
    version : 1.2
    date    : 05/06/16
*/
/* if_type.c */
PRIVATE void PROCEDURE(void)
{
    Node *first, *second;

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
