/*
    module  : formatf.c
    version : 1.2
    date    : 08/21/23
*/
#ifndef FORMATF_C
#define FORMATF_C

/**
OK 1770  formatf  :  DDDDA 	F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
PRIVATE void formatf_(pEnv env)
{
    Node first, second, third, fourth;
    char format[6], *result;
    int leng;

    PARM(4, FORMATF);
    fourth = vec_pop(env->stck); /* min width */
    third = vec_pop(env->stck);  /* max width */
    second = vec_pop(env->stck); /* mode */
    first = vec_pop(env->stck);  /* number */
    strcpy(format, "%*.*g");
    format[4] = second.u.num;
    leng = snprintf(0, 0, format, third.u.num, fourth.u.num, first.u.dbl) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, third.u.num, fourth.u.num, first.u.dbl);
    first.u.str = result;
    first.op = STRING_;
    vec_push(env->stck, first);
}
#endif
