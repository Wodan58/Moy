/* strftime.c */
PRIVATE void strftime_()
{
    struct tm t;
    size_t length;
    char *fmt, *result;

    TWOPARAMS("strftime");
    STRING("strftime");
    fmt = stk->u.str;
    POP(stk);
    LIST("strftime");
    decode_time(&t);
    length = INPLINEMAX;
    result = GC_malloc(length);
    strftime(result, length, fmt, &t);
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
