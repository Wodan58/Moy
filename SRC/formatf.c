/*
    module  : formatf.c
    version : 1.5
    date    : 03/18/17
*/
#include "runtime.h"

/*
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
    if (optimizing && INTEGER_1 && INTEGER_2 && CHAR_3 && FLOAT_4)
	;
    else
	COMPILE;
    FOURPARAMS("formatf");
    INTEGER("formatf");
    INTEGER2("formatf");
#endif
    prec = stk->u.num;
    POP(stk);
    width = stk->u.num;
    POP(stk);
#ifndef NCHECK
    CHARACTER("formatf");
#endif
    spec = stk->u.num;
    POP(stk);
#ifdef RUNTIME_CHECKS
    if (!strchr("eEfgG", spec))
	execerror("one of: e E f g G", "formatf");
#endif
    strcpy(format, "%*.*lg");
    format[5] = spec;
#ifndef NCHECK
    FLOAT("formatf");
#endif
#ifdef _MSC_VER
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, stk->u.dbl) + 1;
#endif
    result = GC_malloc_atomic(leng + 1);
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
