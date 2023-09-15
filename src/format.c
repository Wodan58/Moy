/*
    module  : format.c
    version : 1.6
    date    : 09/15/23
*/
#ifndef FORMAT_C
#define FORMAT_C

/**
OK 1760  format  :  DDDDA	N C I J  ->  S
S is the formatted version of N in mode C
('d or 'i = decimal, 'o = octal, 'x or
'X = hex with lower or upper case letters)
with maximum width I and minimum width J.
*/
PRIVATE void format_(pEnv env)
{
    Node first, second, third, fourth;
    char format[7], *result;
    int leng;

    PARM(4, FORMAT);
    fourth = lst_pop(env->stck); /* min width */
    third = lst_pop(env->stck);  /* max width */
    second = lst_pop(env->stck); /* mode */
    first = lst_pop(env->stck);  /* number */
    strcpy(format, "%*.*ld");
    format[5] = second.u.num;
    leng = snprintf(0, 0, format, third.u.num, fourth.u.num, first.u.num) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, third.u.num, fourth.u.num, first.u.num);
    first.u.str = result;
    first.op = STRING_;
    lst_push(env->stck, first);
}
#endif
