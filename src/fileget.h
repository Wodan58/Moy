/*
    module  : fileget.h
    version : 1.9
    date    : 04/20/19
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
