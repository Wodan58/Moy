/* dipped.c */
PRIVATE void PROCEDURE()
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
