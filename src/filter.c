/*
    module  : filter.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef FILTER_C
#define FILTER_C

/**
OK 2850  filter  :  DDA	A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void filter_(pEnv env)
{
    int i;
    unsigned size;
    Node aggr, list, node;

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
    node.op = aggr.op;
    switch (aggr.op) {
    case LIST_:
        vec_init(node.u.lis);
        vec_push(env->prog, node);
        for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
            /*
                push the element that may be added to the result
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
            code(env, fpush_);
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
        node.u.str = GC_strdup(aggr.u.str);
        node.u.str[0] = 0;
        vec_push(env->prog, node);
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
            code(env, fpush_);
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
            vec_push(env->prog, node);
        }
        break;

    case SET_:
        node.u.set = 0;
        vec_push(env->prog, node);
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
                code(env, fpush_);
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
                vec_push(env->prog, node);
            }
    default:
        break;
    }
}
#endif
