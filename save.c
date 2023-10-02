/*
    module  : save.c
    version : 1.7
    date    : 10/02/23
*/
#include "globals.h"
#include "prim.h"

/*
    Save the stack just before executing a program. Restore it afterwards
    without num items and including the new top of the stack.
*/
PUBLIC void save(pEnv env, NodeList *list, int num, int remove)
{
    Node node;
    int status;

    if (!list)
	goto done;
    if ((status = pvec_getarity(list)) == ARITY_UNKNOWN)
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
    pvec_setarity(list, status);
    if (status == ARITY_NOT_OK) {
done:
	/*
	    replace the new stack with the old stack
	*/
	    code(env, unstack_);	/* the stack is restored with result */
	/*
	    include the test result in the old stack
	*/
	    code(env, cons_);
	/*
	    remove remove items from the old stack
	*/
	while (remove--)
	    code(env, rest_);
	/*
	    restore the old stack after the test
	*/
	node.u.lis = pvec_init();
	pvec_copy(node.u.lis, env->stck); /* the stack is saved as a list */
	node.op = LIST_;
	prime(env, node);
    }
}
