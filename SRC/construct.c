/*
    module  : construct.c
    version : 1.8
    date    : 04/22/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_construct(void)
{
    void *save[3];
    unsigned op, op1;
    Node *cur, *prog;

    save[2] = 0;
    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    cur = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    fprintf(outfp, "{ /* CONSTRUCT */");
    fprintf(outfp, "Node *save[2], *root = 0;");
    fprintf(outfp, "save[0] = stk;");
    save[0] = new_history();
    evaluate2(prog, START_SCOPE);
    for (; cur; cur = cur->next) {
	fprintf(outfp, "CONDITION; save[1] = stk;");
	save[1] = new_history();
	evaluate2(cur->u.lis, MID_SCOPE);
	op = top_history(&op1);
	save[2] = save_history(save[2], op, op1);
	old_history(save[1]);
	fprintf(outfp, "root = heapnode(stk->op, stk->u.ptr, root);");
	fprintf(outfp, "stk = save[1]; RELEASE;");
    }
    old_history(save[0]);
    swap_history(save[2]);
    while (rest_history(save[2], &op, &op1))
	add_history2(op, op1);
    fprintf(outfp, "stk = save[0]; while (root) {");
    fprintf(outfp, "DUPLICATE(root); root = root->next; } }");
    evaluate2(0, STOP_SCOPE);
    return 1;
}
#endif

/*
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
PRIVATE void do_construct(void)
{
    Node *cur, *prog, *root = 0, *save[2];

#ifndef NCHECK
    if (optimizing && put_construct())
	return;
    COMPILE;
    TWOPARAMS("construct");
    TWOQUOTES("construct");
#endif
    cur = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    save[0] = stk;
    exeterm(prog);
    for (; cur; cur = cur->next) {
	CONDITION;
	save[1] = stk;
	exeterm(cur->u.lis);
	root = heapnode(stk->op, stk->u.ptr, root);
	stk = save[1];
	RELEASE;
    }
    stk = save[0];
    for (cur = root; cur; cur = cur->next)
	DUPLICATE(cur);
}
