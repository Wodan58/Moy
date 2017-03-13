/*
    module  : construct.c
    version : 1.6
    date    : 03/12/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_construct(void)
{
    Node *cur, *prog;

    if (!(LIST_1 && LIST_2))
	return 0;
    cur = stk->u.lis;
    POP(stk);
    prog = stk->u.lis;
    POP(stk);
    fprintf(outfp, "{ /* CONSTRUCT */");
    fprintf(outfp, "Node *save[2], *root = 0;");
    fprintf(outfp, "save[0] = stk;");
    evaluate2(prog, START_SCOPE);
    for ( ; cur; cur = cur->next) {
	fprintf(outfp, "CONDITION; save[1] = stk;");
	evaluate2(cur->u.lis, MID_SCOPE);
	fprintf(outfp, "root = heapnode(stk->op, stk->u.ptr, root);");
	fprintf(outfp, "stk = save[1]; RELEASE;");
    }
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
    for ( ; cur; cur = cur->next) {
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
