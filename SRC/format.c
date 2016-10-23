/*
    module  : format.c
    version : 1.3
    date    : 09/19/16
*/
#include "interp.h"

/*
format  :  N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
/* format.c */
PRIVATE void format_(void)
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
#ifdef RUNTIME_CHECKS
    if (!strchr("dioxX", spec))
	execerror("one of: d i o x X", "format");
#endif
    strcpy(format, "%*.*ld");
    format[5] = spec;
#ifdef BIT_32
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, stk->u.num);
#endif
    result = malloc(leng + 1);
    NUMERICTYPE("format");
#ifdef BIT_32
    sprintf(result, format, width, prec, stk->u.num);
#else
    snprintf(result, leng, format, width, prec, stk->u.num);
#endif
    if (OUTSIDE) {
	stk->u.str = result;
	stk->op = STRING_;
    } else
	UNARY(STRING_NEWNODE, result);
}
