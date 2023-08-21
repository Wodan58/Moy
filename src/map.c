/*
    module  : map.c
    version : 1.3
    date    : 08/21/23
*/
#ifndef MAP_C
#define MAP_C

/**
OK 2810  map  :  DDA	A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void map_(pEnv env)
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
        for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
            /*
                push the location of the result type
            */
            push(env, size);
            /*
                add an instruction that builds the result type
            */
            code(env, push_);
            /*
                save and restore the stack, if needed
            */
            save(env, list.u.lis, 1);
            /*
                push the program to be executed for each element
            */
            prog(env, list.u.lis);
            /*
                push the element to be mapped
            */
            node = vec_at(aggr.u.lis, i);
            prime(env, node);
        }
        break;

    case STRING_:
    case BIGNUM_:
        temp.u.str = GC_strdup(aggr.u.str);
        temp.u.str[0] = 0;
        vec_push(env->prog, temp);
        node.op = CHAR_;
        for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
            /*
                push the location of the result type
            */
            push(env, size);
            /*
                add an instruction that builds the result type
            */
            code(env, push_);
            /*
                save and restore the stack, if needed
            */
            save(env, list.u.lis, 1);
            /*
                push the program to be executed for each element
            */
            prog(env, list.u.lis);
            /*
                push the element to be mapped
            */
            node.u.num = aggr.u.str[i];
            vec_push(env->prog, node);
        }
        break;

    case SET_:
        temp.u.set = 0;
        vec_push(env->prog, temp);
        node.op = INTEGER_;
        for (i = 0; i < SETSIZE; i++)
            if (aggr.u.set & ((int64_t)1 << i)) {
                /*
                    push the location of the result type
                */
                push(env, size);
                /*
                    add an instruction that builds the result type
                */
                code(env, push_);
                /*
                    save and restore the stack, if needed
                */
                save(env, list.u.lis, 1);
                /*
                    push the program to be executed for each element
                */
                prog(env, list.u.lis);
                /*
                    push the element to be mapped
                */
                node.u.num = i;
                vec_push(env->prog, node);
            }
    default:
        break;
    }
}
#endif
