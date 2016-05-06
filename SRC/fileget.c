/*
    module  : fileget.c
    version : 1.2
    date    : 05/06/16
*/
/* fileget.c */
PRIVATE void PROCEDURE(void)
{
    ONEPARAM(NAME);
    FILE(NAME);
    PUSH(CONSTRUCTOR, EXPR);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef EXPR
