/* fopen.c */
PRIVATE void fopen_()
{
    TWOPARAMS("fopen");
    STRING("fopen");
    STRING2("fopen");
    if (OUTSIDE) {
	stk->next->u.fil = fopen(stk->next->u.str, stk->u.str);
	stk->next->op = FILE_;
	POP(stk);
    } else
	BINARY(FILE_NEWNODE, fopen(stk->next->u.str, stk->u.str));
}
