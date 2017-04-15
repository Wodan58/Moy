/*
    module  : fileget.c
    version : 1.4
    date    : 04/09/17
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef NCHECK
    if (optimizing)
	add_history(CONSTRUCTOR);
    COMPILE;
    ONEPARAM(NAME);
    FILE(NAME);
#endif
    temp.op = CONSTRUCTOR;
    temp.u.ptr = (void *)EXPR;
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef EXPR
