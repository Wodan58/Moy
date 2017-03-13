/*
    module  : dipped.c
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
    Node save;

#ifndef NCHECK
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    PARAMCOUNT(NAME);
#endif
    save = *stk;
    POP(stk);
    ARGUMENT();
    DUPLICATE(&save);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef ARGUMENT
