/*
    module  : infra.c
    version : 1.5
    date    : 10/04/16
*/
#include "interp.h"

/*
    Copy the stack to a list
*/
Node *stk2lst()
{
    Node *root = 0, **cur;

    for (cur = &root; stk && stk != &memory[MEMORYMAX]; stk = stk->next) {
	*cur = heapnode(stk->op, stk->u.ptr, 0);
	cur = &(*cur)->next;
    }
    return root;
}

/*
    Replace the stack by a list
*/
void lst2stk(Node *cur)
{
    if (cur) {
	lst2stk(cur->next);
	DUPLICATE(cur);
    }
}

/*
infra  :  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
/* infra.c */
PRIVATE void infra_(void)
{
    Node *prog, *list, *save;

/*
 1. Register the program
 2. Register the list
 3. Make a backup of the stack, starting with save
 4. Empty the stack
 5. Copy the list onto the stack
 6. Execute prog
 7. Collect the stack into the list
 8. Empty the stack
 9. Restore the original stack
10. Put the collected list onto the stack
*/
    TWOPARAMS("infra");
    ONEQUOTE("infra");
    LIST2("infra");
    prog = stk->u.lis;		// 1
    POP(stk);
    list = stk->u.lis;		// 2
    POP(stk);
    save = stk2lst();		// 3, 4
    lst2stk(list);		// 5
    exeterm(prog);		// 6
    list = stk2lst();		// 7, 8
    lst2stk(save);		// 9
    PUSH(LIST_, list);		// 10
}
