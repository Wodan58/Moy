/*
    module  : primrec.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef PRIMREC_C
#define PRIMREC_C

/**
OK 2840  primrec  :  DDDA	X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void primrec_(pEnv env)
{
    char *str;
    int i, j = 0;
    Node first, second, third, node;

    PARM(3, PRIMREC);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    switch (first.op) {
    case LIST_:
        j = vec_size(first.u.lis);
        for (i = j - 1; i >= 0; i--) {
            node = vec_at(first.u.lis, i);
            vec_push(env->stck, node);
        }
        break;
 
    case STRING_:
    case BIGNUM_:
        node.op = CHAR_;
        j = strlen(first.u.str);
        for (str = first.u.str; *str; str++) {
            node.u.num = *str;
            vec_push(env->stck, node);
        }
        break;

    case SET_:
        node.op = INTEGER_;
        for (j = i = 0; i < SETSIZE; i++)
            if (first.u.set & ((int64_t)1 << i)) {
                node.u.num = i;
                vec_push(env->stck, node);
                j++;
            }
        break;
 
    case INTEGER_:
        node.op = INTEGER_;
        for (j = i = first.u.num; i > 0; i--) {
            node.u.num = i;
            vec_push(env->stck, node);
        }
    default:
        break;
    }
    for (i = 0; i < j; i++)
        prog(env, third.u.lis);
    prog(env, second.u.lis);
}
#endif
