/*
    module  : fileget.h
    version : 1.11
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
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
