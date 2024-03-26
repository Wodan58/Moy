/*
    module  : save.c
    version : 1.12
    date    : 03/21/24
*/
#include "globals.h"
#include "prim.h"

/*
 * Save the stack just before executing a program. Restore it afterwards
 * without num items and including the new top of the stack.
 */
void save(pEnv env, NodeList *list, int num, int remove)
{
    Node node;
    int status;

    if (!list)
	goto done;
    /*
     * If the status is UNKNOWN, it needs to be calculated. Once calculated,
     * it is either OK or NOT_OK. In both cases, the status is KNOWN and need
     * not be calculated again. In case it is NOT_OK, the entire stack needs
     * to be saved and restored.
     */
    if ((status = pvec_getarity(list)) == ARITY_UNKNOWN) {
	status = arity(env, list, num) == 1 ? ARITY_OK : ARITY_NOT_OK;
	if (env->overwrite) {
	    printf("%s: (", status == ARITY_OK ? "info" : "warning");
	    writeterm(env, list, stdout);
	    printf(") has %scorrect arity\n", status == ARITY_OK ?  "" : "in");
	}
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
