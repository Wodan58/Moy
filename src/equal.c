/*
    module  : equal.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef EQUAL_C
#define EQUAL_C

/**
OK 2290  equal  :  DDA	T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
PRIVATE int compatible(int first, int second)
{
    switch (first) {
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
    case FLOAT_:
    case SET_:
        switch (second) {
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case FLOAT_:
        case SET_:
            return 1;

        default:
            return 0;
        }
        break;

    case USR_:
    case ANON_FUNCT_:
    case STRING_:
        switch (second) {
        case USR_:
        case ANON_FUNCT_:
        case STRING_:
            return 1;

        default:
            return 0;
        }
    default:
        break;
    }
    return first == second;
}

PRIVATE int is_equal(pEnv env, Node first, Node second)
{
    int i, j;
    Node temp;
    NodeList *stackf = 0, *stacks = 0;

    if (!compatible(first.op, second.op))
        return 0; /* unequal */
    if (first.op != LIST_)
        return Compare(env, first, second) == 0;
    if ((j = vec_size(first.u.lis)) != vec_size(second.u.lis))
        return 0; /* unequal */
    if (j) {
        vec_init(stackf);
        vec_init(stacks);
    }
    for (i = 0; i < j; i++) {
        temp = vec_at(first.u.lis, i);
        vec_push(stackf, temp);
        temp = vec_at(second.u.lis, i);
        vec_push(stacks, temp);
    }
    while (vec_size(stackf)) {
        first = vec_pop(stackf);
        second = vec_pop(stacks);
        if (!compatible(first.op, second.op))
            return 0; /* unequal */
        if (first.op != LIST_) {
            if (Compare(env, first, second))
                return 0; /* unequal */
        } else {
            if ((j = vec_size(first.u.lis)) != vec_size(second.u.lis))
                return 0; /* unequal */
            for (i = 0; i < j; i++) {
                temp = vec_at(first.u.lis, i);
                vec_push(stackf, temp);
                temp = vec_at(second.u.lis, i);
                vec_push(stacks, temp);
            }            
        }
    }
    return 1; /* equal */
}

void equal_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first.u.num = is_equal(env, first, second);
    first.op = BOOLEAN_;
    vec_push(env->stck, first);
}
#endif
