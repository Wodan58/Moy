/*
    module  : dipped.h
    version : 1.11
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    Node *save;

    PARAMCOUNT(NAME);
    save = env->stk;
    POP(env->stk);
    ARGUMENT(env);
    DUPLICATE(save);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef ARGUMENT
