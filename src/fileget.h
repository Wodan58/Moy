/*
    module  : fileget.h
    version : 1.7
    date    : 07/15/18
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM(NAME);
    FILE(NAME);
    temp.op = CONSTRUCTOR;
    temp.u.ptr = (void *)EXPR;
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef EXPR
