/*
    module  : formatf.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef FORMATF_C
#define FORMATF_C

/**
formatf  :  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
PRIVATE void do_formatf(pEnv env)
{
    int width, prec, leng;
    char spec, format[7], *result;

    FOURPARAMS("formatf");
    INTEGER("formatf");
    INTEGER2("formatf");
    prec = env->stk->u.num;
    POP(env->stk);
    width = env->stk->u.num;
    POP(env->stk);
    CHARACTER("formatf");
    spec = env->stk->u.num;
    POP(env->stk);
    CHECKFORMATF(spec, "formatf");
    strcpy(format, "%*.*g");
    format[4] = spec;
    FLOAT("formatf");
    leng = snprintf(0, 0, format, width, prec, env->stk->u.dbl) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, width, prec, env->stk->u.dbl);
    UNARY(STRING_NEWNODE, result);
}
#endif
