/*
    module  : save.c
    version : 1.6
    date    : 09/14/23
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
    if ((status = lst_getarity(list)) == ARITY_UNKNOWN)
        status = arity(env, list, num) == 1 ? ARITY_OK : ARITY_KNOWN;
    if (status == ARITY_KNOWN) {
#ifdef ARITY
	if (env->overwrite) {
            printf("arity: ");
            writeterm(env, list, stdout);
            printf("\n");
	}
#endif
        status = ARITY_NOT_OK;
    }
    lst_setarity(list, status);
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
        lst_init(node.u.lis);
        lst_copy(node.u.lis, env->stck);
        node.op = LIST_;
        lst_push(env->prog, node);
    }
}
