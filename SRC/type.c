/* type.c */
PRIVATE void PROCEDURE()
{
    ONEPARAM(NAME);
    if (OUTSIDE) {
	stk->u.num = stk->op REL TYP;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, (stk->op REL TYP));
}

#undef PROCEDURE
#undef NAME
#undef REL
#undef TYP
