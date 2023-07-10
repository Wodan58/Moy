/*
    module  : concat.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
OK 2160  concat  :  DDA	S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void concat_(pEnv env)
{
    int i, j;
    Node first, second, result;

    PARM(2, CONCAT);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    switch (first.op) {
    case LIST_:
        if (!vec_size(first.u.lis))
            result = second;
        else if (!vec_size(second.u.lis))
            result = first;
        else {
            vec_init(result.u.lis);
            vec_copy(result.u.lis, second.u.lis);
            for (i = 0, j = vec_size(first.u.lis); i < j; i++)
                vec_push(result.u.lis, vec_at(first.u.lis, i));
        }
        break;

    case STRING_:
        i = strlen(first.u.str);
        j = strlen(second.u.str);
        result.u.str = GC_malloc_atomic(i + j + 1);
        strcpy(result.u.str, first.u.str);
        strcpy(result.u.str + i, second.u.str);
        break;

    case SET_:
        result.u.set = first.u.set | second.u.set;
    default:
        break;
    }
    result.op = first.op;
    vec_push(env->stck, result);
}
#endif
