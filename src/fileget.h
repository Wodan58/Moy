/*
    module  : fileget.h
    version : 1.5
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
    Node temp;

#ifndef NCHECK
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
