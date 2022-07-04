/*
    module  : fileget.h
    version : 1.12
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    COMPILE;
    ONEPARAM(NAME);
    FILE(NAME);
    NULLARY(CONSTRUCTOR, EXPR);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef EXPR
