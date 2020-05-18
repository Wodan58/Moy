/*
    module  : fileget.h
    version : 1.10
    date    : 03/28/20
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
    temp.u.num = EXPR;
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef EXPR
