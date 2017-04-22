/*
    module  : dipped.c
    version : 1.5
    date    : 04/22/17
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef NCHECK
    unsigned op = 0, op1;

    if (optimizing) {
	op = pop_history(&op1);
	del_history(1);
    }
    if (optimizing && VALID(stk) && VALID(stk->next))
	;
    else
	COMPILE;
    PARAMCOUNT(NAME);
#endif
    temp = *stk;
    POP(stk);
    ARGUMENT();
    DUPLICATE(&temp);
#ifndef NCHECK
    if (optimizing)
	add_history2(op, op1);
#endif
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef ARGUMENT
