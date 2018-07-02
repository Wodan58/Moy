/*
    module  : dipped.h
    version : 1.6
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef NCHECK
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    PARAMCOUNT(NAME);
    temp = *stk;
    POP(stk);
    ARGUMENT();
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef ARGUMENT
