/*
    module  : format.c
    version : 1.10
    date    : 07/10/18
*/
#ifndef FORMAT_X
#define FORMAT_C

/**
format  :  N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
PRIVATE void do_format(void)
{
    int width, prec, leng;
    char spec, format[8], *result;

#ifndef NCHECK
    if (compiling && INTEGER_1 && INTEGER_2 && CHAR_3 && NUMERIC_4)
	;
    else
	COMPILE;
#endif
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
    strcpy(format, "%*.*lld");
    format[6] = spec;
    NUMERICTYPE("format");
#ifdef _MSC_VER
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, (long long)stk->u.num) + 1;
#endif
    result = ck_malloc_sec(leng + 1);
#ifdef _MSC_VER
    sprintf(result, format, width, prec, (long long)stk->u.num);
#else
    snprintf(result, leng, format, width, prec, (long long)stk->u.num);
#endif
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
#endif
