/*
    module  : dipped.c
    version : 1.2
    date    : 05/06/16
*/
/* dipped.c */
PRIVATE void PROCEDURE(void)
{
    Node save;

    PARAMCOUNT(NAME);
    save = *stk;
    POP(stk);
    ARGUMENT();
    DUPLICATE(&save);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef ARGUMENT
