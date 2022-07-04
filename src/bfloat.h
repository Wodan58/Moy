/*
    module  : bfloat.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    TWOPARAMS(NAME);
    FLOAT2(NAME);
    BINARY(FLOAT_NEWNODE, FUNC(FLOATVAL2, FLOATVAL));
}

#undef PROCEDURE
#undef NAME
#undef FUNC
