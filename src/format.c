/*
    module  : format.c
    version : 1.14
    date    : 06/20/22
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
    CHECKFORMAT(spec, "format");
    strcpy(format, "%*.*ld");
    format[5] = spec;
    NUMERICTYPE("format");
    leng = snprintf(0, 0, format, width, prec, (long)env->stk->u.num) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, width, prec, (long)env->stk->u.num);
    UNARY(STRING_NEWNODE, result);
}
#endif
