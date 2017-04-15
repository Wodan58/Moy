/*
    module  : format.c
    version : 1.7
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
    if (optimizing) {
	del_history(3);
	chg_history(STRING_);
    }
    if (optimizing && INTEGER_1 && INTEGER_2 && CHAR_3 && NUMERIC_4)
	;
    else
	COMPILE;
    FOURPARAMS("format");
    INTEGER("format");
    INTEGER2("format");
#endif
    prec = stk->u.num;
    POP(stk);
    width = stk->u.num;
    POP(stk);
#ifndef NCHECK
    CHARACTER("format");
#endif
    spec = stk->u.num;
    POP(stk);
#ifndef NCHECK
    if (!strchr("dioxX", spec))
	execerror("one of: d i o x X", "format");
#endif
    strcpy(format, "%*.*lld");
    format[6] = spec;
#ifndef NCHECK
    NUMERICTYPE("format");
#endif
#ifdef _MSC_VER
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, (long long)stk->u.num) + 1;
#endif
    result = GC_malloc_atomic(leng + 1);
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
