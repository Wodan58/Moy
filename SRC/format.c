/* format.c */
PRIVATE void format_()
{
    int width, prec, leng;
    char spec, format[7], *result;

    FOURPARAMS("format");
    INTEGER("format");
    INTEGER2("format");
    prec = stk->u.num;
    POP(stk);
    width = stk->u.num;
    POP(stk);
    CHARACTER("format");
    spec = stk->u.num;
    POP(stk);
    if (!strchr("dioxX", spec))
	execerror("one of: d i o x X", "format");
    strcpy(format, "%*.*ld");
    format[5] = spec;
    leng = snprintf(0, 0, format, width, prec, stk->u.num);
    result = GC_malloc(leng + 1);
    NUMERICTYPE("format");
    snprintf(result, leng, format, width, prec, stk->u.num);
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
