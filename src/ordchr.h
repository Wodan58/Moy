/*
    module  : ordchr.h
    version : 1.12
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    UNARY(RESULTTYP, env->stk->u.num);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
