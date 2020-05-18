/*
    module  : dipped.h
    version : 1.9
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef OLD_RUNTIME
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
