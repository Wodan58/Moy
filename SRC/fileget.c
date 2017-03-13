/*
    module  : fileget.c
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef NCHECK
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
