/*
    module  : formatf.c
    version : 1.12
    date    : 03/15/21
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

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && INTEGER_2 && CHAR_3 && FLOAT_4)
	;
    else
	COMPILE;
#endif
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
#ifndef NCHECK
    if (!strchr("eEfgG", spec))
	execerror("one of: e E f g G", "formatf");
#endif
    strcpy(format, "%*.*g");
    format[5] = spec;
    FLOAT("formatf");
#ifdef _MSC_VER
    leng = INPLINEMAX;
#else
    leng = snprintf(0, 0, format, width, prec, (double)env->stk->u.dbl) + 1;
#endif
    result = GC_malloc_atomic(leng + 1);
#ifdef _MSC_VER
    sprintf(result, format, width, prec, (double)env->stk->u.dbl);
#else
    snprintf(result, leng, format, width, prec, (double)env->stk->u.dbl);
#endif
    env->stk->u.str = result;
    env->stk->op = STRING_;
}
#endif
