/*
    module  : save.c
    version : 1.3
    date    : 07/18/23
*/
#include "globals.h"
#include "prim.h"

/*
    Save the stack just before executing a condition. Restore it afterwards
    with the condition code included.
*/
PUBLIC void save(pEnv env, NodeList *list, int num)
{
    Node node;
    int status;

    if (!list)
        goto done;
    if ((status = vec_getarity(list)) == ARITY_UNKNOWN)
        status = arity(env, list, num) == 1 ? ARITY_OK : ARITY_KNOWN;
    if (status == ARITY_KNOWN) {
#ifdef ARITY
        printf("arity: ");
        writeterm(env, list);
        printf("\n");
#endif
        status = ARITY_NOT_OK;
    }
    vec_setarity(list, status);
    if (status == ARITY_NOT_OK) {
done:
        /*
            replace the new stack with the old stack
        */
        code(env, unstack_);
        /*
            include the test result in the old stack
        */
        code(env, cons_);
        /*
            restore the old stack after the test
        */
        vec_init(node.u.lis);
        vec_copy(node.u.lis, env->stck);
        node.op = LIST_;
        vec_push(env->prog, node);
    }
}
