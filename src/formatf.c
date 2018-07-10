/*
    module  : formatf.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef FORMATF_X
#define FORMATF_C

/**
formatf  :  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
PRIVATE void do_formatf(void)
{
    int width, prec, leng;
    char spec, format[7], *result;

#ifndef NCHECK
    if (compiling && INTEGER_1 && INTEGER_2 && CHAR_3 && FLOAT_4)
	;
    else
	COMPILE;
#endif
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
    FLOAT("formatf");
#ifdef _MSC_VER
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, stk->u.dbl) + 1;
#endif
    result = ck_malloc_sec(leng + 1);
#ifdef _MSC_VER
    sprintf(result, format, width, prec, stk->u.dbl);
#else
    snprintf(result, leng, format, width, prec, stk->u.dbl);
#endif
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
#endif
