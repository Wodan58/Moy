/*
    module  : all.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef ALL_C
#define ALL_C

/**
OK 2880  all  :  DDA	A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void all_(pEnv env)
{
    int i;
    unsigned size;
    Node aggr, list, node;

    PARM(2, STEP);
    size = vec_size(env->prog);
    /*
        if all tests pass, the result will be true.
    */
    code(env, true_);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
            /*
                push the location of the result type
            */
            push(env, size);
            /*
                add an instruction that builds the result type
            */
            code(env, jfalse_);
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
        node.op = CHAR_;
        for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
            /*
                push the location of the result type
            */
            push(env, size);
            /*
                add an instruction that builds the result type
            */
            code(env, jfalse_);
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
                code(env, jfalse_);
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
