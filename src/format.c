/*
    module  : format.c
    version : 1.10
    date    : 04/11/24
*/
#ifndef FORMAT_C
#define FORMAT_C

/**
Q0  OK  1760  format  :  DDDDA  N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
void format_(pEnv env)
{
    int leng;
    char format[MAXNUM], *result;
    Node first, second, third, fourth;

    PARM(4, FORMAT);
    env->stck = pvec_pop(env->stck, &fourth);	/* min width */
    env->stck = pvec_pop(env->stck, &third);	/* max width */
    env->stck = pvec_pop(env->stck, &second);	/* mode */
    env->stck = pvec_pop(env->stck, &first);	/* number */
    strcpy(format, "%*.*lld");
    format[6] = second.u.num;
    leng = snprintf(0, 0, format, third.u.num, fourth.u.num, first.u.num) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, third.u.num, fourth.u.num, first.u.num);
    first.u.str = result;
    first.op = STRING_;
    env->stck = pvec_add(env->stck, first);
}
#endif
