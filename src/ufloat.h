/*
    module  : ufloat.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    ONEPARAM(NAME);
    FLOAT(NAME);
    UNARY(FLOAT_NEWNODE, FUNC(FLOATVAL));
}

#undef PROCEDURE
#undef NAME
#undef FUNC
