/* fclose.c */
PRIVATE void fclose_()
{
    ONEPARAM("fclose");
    FILE("fclose");
    if (stk->u.fil)
	fclose(stk->u.fil);
    POP(stk);
}
