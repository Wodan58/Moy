/*
    module  : format.c
    version : 1.11
    date    : 09/17/24
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
    fourth = vec_pop(env->stck);	/* min width */
    third = vec_pop(env->stck);		/* max width */
    second = vec_pop(env->stck);	/* mode */
    first = vec_pop(env->stck);		/* number */
    strcpy(format, "%*.*lld");
    format[6] = second.u.num;
    leng = snprintf(0, 0, format, third.u.num, fourth.u.num, first.u.num) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, third.u.num, fourth.u.num, first.u.num);
    first.u.str = result;
    first.op = STRING_;
    vec_push(env->stck, first);
}
#endif
