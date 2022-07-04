/*
    module  : type.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    ONEPARAM(NAME);
    UNARY(BOOLEAN_NEWNODE, env->stk->op REL TYP);
}

#undef PROCEDURE
#undef NAME
#undef REL
#undef TYP
