/*
    module  : formatf.c
    version : 1.10
    date    : 04/11/24
*/
#ifndef FORMATF_C
#define FORMATF_C

/**
Q0  OK  1770  formatf  :  DDDDA  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
void formatf_(pEnv env)
{
    int leng;
    char format[MAXNUM], *result;
    Node first, second, third, fourth;

    PARM(4, FORMATF);
    env->stck = pvec_pop(env->stck, &fourth);	/* min width */
    env->stck = pvec_pop(env->stck, &third);	/* max width */
    env->stck = pvec_pop(env->stck, &second);	/* mode */
    env->stck = pvec_pop(env->stck, &first);	/* number */
    strcpy(format, "%*.*g");
    format[4] = second.u.num;
    leng = snprintf(0, 0, format, third.u.num, fourth.u.num, first.u.dbl) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, third.u.num, fourth.u.num, first.u.dbl);
    first.u.str = result;
    first.op = STRING_;
    env->stck = pvec_add(env->stck, first);
}
#endif
