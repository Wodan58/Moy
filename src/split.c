/*
    module  : split.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef SPLIT_C
#define SPLIT_C

/**
OK 2860  split  :  DDAA	A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void split_(pEnv env)
{
    int i;
    unsigned size;
    Node aggr, list, node, temp;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    /*
        register the location of the result aggregate
    */
    size = vec_size(env->prog);
    /*
        build a result aggregate of the correct type
    */
    temp.op = aggr.op;
    switch (aggr.op) {
    case LIST_:
        vec_init(temp.u.lis);
        vec_push(env->prog, temp);
        vec_init(temp.u.lis);
        vec_push(env->prog, temp);
        for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
            /*
                push the element to be split
            */
            node = vec_at(aggr.u.lis, i);
            prime(env, node);
            /*
                push the location of the result types
            */
            push(env, size);
            /*
                add an instruction that builds the result types
            */
            code(env, tpush_);
            /*
                save and restore the stack, if needed
            */
            save(env, list.u.lis, 1);
            /*
                push the program to be executed for each element
            */
            prog(env, list.u.lis);
            /*
                push the element to be split
            */
            prime(env, node);
        }
        break;

    case STRING_:
    case BIGNUM_:
        temp.u.str = GC_strdup(aggr.u.str);
        temp.u.str[0] = 0;
        vec_push(env->prog, temp);
        temp.u.str = GC_strdup(aggr.u.str);
        temp.u.str[0] = 0;
        vec_push(env->prog, temp);
        node.op = CHAR_;
        for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
            /*
                push the element that may be added to the result
            */
            node.u.num = aggr.u.str[i];
            vec_push(env->prog, node);
            /*
                push the location of the result types
            */
            push(env, size);
            /*
                add an instruction that builds the result types
            */
            code(env, tpush_);
            /*
                save and restore the stack, if needed
            */
            save(env, list.u.lis, 1);
            /*
                push the program to be executed for each element
            */
            prog(env, list.u.lis);
            /*
                push the element that may be added to the result
            */
            vec_push(env->prog, node);
        }
        break;

    case SET_:
        temp.u.set = 0;
        vec_push(env->prog, temp);
        vec_push(env->prog, temp);
        node.op = INTEGER_;
        for (i = 0; i < SETSIZE; i++)
            if (aggr.u.set & ((int64_t)1 << i)) {
                /*
                    push the element that may be added to the result
                */
                node.u.num = i;
                vec_push(env->prog, node);
                /*
                    push the location of the result types
                */
                push(env, size);
                /*
                    add an instruction that builds the result types
                */
                code(env, tpush_);
                /*
                    save and restore the stack, if needed
                */
                save(env, list.u.lis, 1);
                /*
                    push the program to be executed for each element
                */
                prog(env, list.u.lis);
                /*
                    push the element that may be added to the result
                */
                vec_push(env->prog, node);
            }
    default:
        break;
    }
}
#endif
