/*
    module  : formatf.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
formatf  :  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
/* formatf.c */
PRIVATE void formatf_(void)
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
#ifdef RUNTIME_CHECKS
    if (!strchr("eEfgG", spec))
	execerror("one of: e E f g G", "formatf");
#endif
    strcpy(format, "%*.*lg");
    format[5] = spec;
#ifdef BIT_32
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, stk->u.num);
#endif
    result = GC_malloc(leng + 1);
    FLOAT("formatf");
#ifdef BIT_32
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
