/* if_type.c */
PRIVATE void PROCEDURE()
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
