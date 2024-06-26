/*
    module  : save.c
    version : 1.13
    date    : 05/06/24
*/
#include "globals.h"
#include "prim.h"

/*
 * Save the stack just before executing a program. Restore it afterwards
 * without num items and including the new top of the stack.
 */
void save(pEnv env, NodeList *list, int num, int remove)
{
    FILE *fp;
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
	    /*
	     * Arities are reported in a log file, because the screen may be
	     * cleared right after displaying a message.
	     */
	    if ((fp = fopen("joy.log", "a")) != 0) {
		fprintf(fp, "%s: (", status == ARITY_OK ? "info" : "warning");
		writeterm(env, list, fp);
		fprintf(fp, ") has %scorrect arity\n", status == ARITY_OK ?
			"" : "in");
		fclose(fp);
	    }
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
