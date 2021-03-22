/*
    module  : format.c
    version : 1.13
    date    : 03/15/21
*/
#ifndef FORMAT_C
#define FORMAT_C

/**
format  :  N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
PRIVATE void do_format(pEnv env)
{
    int width, prec, leng;
    char spec, format[8], *result;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && INTEGER_2 && CHAR_3 && NUMERIC_4)
	;
    else
	COMPILE;
#endif
    FOURPARAMS("format");
    INTEGER("format");
    INTEGER2("format");
    prec = env->stk->u.num;
    POP(env->stk);
    width = env->stk->u.num;
    POP(env->stk);
    CHARACTER("format");
    spec = env->stk->u.num;
    POP(env->stk);
#ifndef NCHECK
    if (!strchr("dioxX", spec))
	execerror("one of: d i o x X", "format");
#endif
    strcpy(format, "%*.*ld");
    format[6] = spec;
    NUMERICTYPE("format");
#ifdef _MSC_VER
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, (long)env->stk->u.num) + 1;
#endif
    result = GC_malloc_atomic(leng + 1);
#ifdef _MSC_VER
    sprintf(result, format, width, prec, (long)env->stk->u.num);
#else
    snprintf(result, leng, format, width, prec, (long)env->stk->u.num);
#endif
    env->stk->u.str = result;
    env->stk->op = STRING_;
}
#endif
