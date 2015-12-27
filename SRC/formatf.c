/* formatf.c */
PRIVATE void formatf_()
{
    int width, prec, leng;
    char spec, format[7], *result;

    FOURPARAMS("formatf");
    INTEGER("formatf");
    INTEGER2("formatf");
    prec = stk->u.num;
    POP(stk);
    width = stk->u.num;
    POP(stk);
    CHARACTER("formatf");
    spec = stk->u.num;
    POP(stk);
    if (!strchr("eEfgG", spec))
	execerror("one of: e E f g G", "formatf");
    strcpy(format, "%*.*lg");
    format[5] = spec;
    leng = snprintf(0, 0, format, width, prec, stk->u.num);
    result = GC_malloc(leng + 1);
    FLOAT("formatf");
    snprintf(result, leng, format, width, prec, stk->u.dbl);
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
