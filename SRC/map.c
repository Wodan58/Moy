/*
    module  : map.c
    version : 1.12
    date    : 04/15/17
*/
#include "runtime.h"

PRIVATE Node *backup(void);
PRIVATE void restore(Node *cur);

#ifndef NCHECK
int put_map(void)
{
    void *save;
    Node *prog;
    unsigned op, op1;

    del_history(1);
    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    if ((op = pop_history(&op1)) == LIST_) {
	fprintf(outfp, "{ /* MAP-LIST */");
	fprintf(outfp, "assert(stk->op == LIST_);");
	fprintf(outfp, "Node *cur, *back = 0, *save, *root = 0, *last = 0;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
	fprintf(outfp, "if (OUTSIDE) back = backup(); else CONDITION;");
	fprintf(outfp, "save = stk; DUPLICATE(cur);");
	add_history(op1);
	evaluate(prog);
	op = top_history(&op1);
	chg_history2(LIST_, op);
	fprintf(outfp, "if (!root)");
	fprintf(outfp, "last = root = heapnode(stk->op, stk->u.ptr, 0); else ");
	fprintf(outfp, "last = last->next = heapnode(stk->op, stk->u.ptr, 0);");
	fprintf(outfp, "stk = save; if (OUTSIDE) restore(back); else RELEASE;");
	fprintf(outfp, "} PUSH(LIST_, root); }");
    } else if (op == STRING_) {
	fprintf(outfp, "{ /* MAP-STRING */");
	fprintf(outfp, "assert(stk->op == STRING_);");
	fprintf(outfp, "char *str, *ptr;");
	fprintf(outfp, "Node *cur, *back = 0, *save;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "str = cur->u.str;");
	fprintf(outfp, "for (ptr = strdup(str); *str; str++) {");
	fprintf(outfp, "if (OUTSIDE) back = backup(); else CONDITION;");
	fprintf(outfp, "save = stk; PUSH(CHAR_, (long_t)*str);");
	add_history(CHAR_);
	evaluate(prog);
	chg_history(STRING_);
	fprintf(outfp, "ptr[i++] = stk->u.num;");
	fprintf(outfp, "stk = save; if (OUTSIDE) restore(back); else RELEASE;");
	fprintf(outfp, "} PUSH(STRING_, ptr); }");
    } else if (op == SET_) {
	fprintf(outfp, "{ /* MAP-SET */");
	fprintf(outfp, "assert(stk->op == SET_);");
	fprintf(outfp, "ulong_t set, zet; unsigned i = 0;");
	fprintf(outfp, "Node *cur, *back = 0, *save;");
	fprintf(outfp, "cur = stk; POP(stk);");
	fprintf(outfp, "set = cur->u.set;");
	fprintf(outfp, "for (zet = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "if (OUTSIDE) back = backup(); else CONDITION;");
	fprintf(outfp, "save = stk; PUSH(INTEGER_, i);");
	add_history(INTEGER_);
	evaluate(prog);
	chg_history(SET_);
	fprintf(outfp, "zet |= 1 << stk->u.num;");
	fprintf(outfp, "stk = save; if (OUTSIDE) restore(back); else RELEASE;");
	fprintf(outfp, "} PUSH(SET_, zet); }");
    } else {
	fprintf(outfp, "{ /* MAP-GENERIC */");
	fprintf(outfp, "char *str, *ptr; ulong_t set, zet; unsigned i = 0;");
	fprintf(outfp, "Node *cur, *back = 0, *save, *root = 0, *last = 0;");
	fprintf(outfp, "cur = stk; POP(stk); switch (cur->op) {");
	fprintf(outfp, "case LIST_:");
	fprintf(outfp, "for (cur = cur->u.lis; cur; cur = cur->next) {");
	fprintf(outfp, "if (OUTSIDE) back = backup(); else CONDITION;");
	fprintf(outfp, "save = stk; DUPLICATE(cur);");
	save = new_history();
	add_history(INTEGER_);
	evaluate(prog);
	fprintf(outfp, "if (!root)");
	fprintf(outfp, "last = root = heapnode(stk->op, stk->u.ptr, 0); else ");
	fprintf(outfp, "last = last->next = heapnode(stk->op, stk->u.ptr, 0);");
	fprintf(outfp, "stk = save; if (OUTSIDE) restore(back); else RELEASE;");
	fprintf(outfp, "} PUSH(LIST_, root); break;");
	fprintf(outfp, "case STRING_:");
	fprintf(outfp, "str = cur->u.str;");
	fprintf(outfp, "for (ptr = strdup(str); *str; str++) {");
	fprintf(outfp, "if (OUTSIDE) back = backup(); else CONDITION;");
	fprintf(outfp, "save = stk; PUSH(CHAR_, (long_t)*str);");
	old_history(save);
	add_history(CHAR_);
	evaluate(prog);
	fprintf(outfp, "ptr[i++] = stk->u.num;");
	fprintf(outfp, "stk = save; if (OUTSIDE) restore(back); else RELEASE;");
	fprintf(outfp, "} PUSH(STRING_, ptr); break;");
	fprintf(outfp, "case SET_:");
	fprintf(outfp, "set = cur->u.set;");
	fprintf(outfp, "for (zet = 0; i < SETSIZE_; i++)");
	fprintf(outfp, "if (set & (1 << i)) {");
	fprintf(outfp, "if (OUTSIDE) back = backup(); else CONDITION;");
	fprintf(outfp, "save = stk; PUSH(INTEGER_, i);");
	old_history(save);
	add_history(INTEGER_);
	evaluate(prog);
	fprintf(outfp, "zet |= 1 << stk->u.num;");
	fprintf(outfp, "stk = save; if (OUTSIDE) restore(back); else RELEASE;");
	fprintf(outfp, "} PUSH(SET_, zet); break; } }");
    }
    return 1;
}
#endif

/*
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
PRIVATE void do_map(void)
{
    Node *prog, *cur,
	 *root = 0, *last = 0, *save, *back = 0;
    int i = 0;
    char *str, *ptr;
    ulong_t set, zet;

#ifndef NCHECK
    if (optimizing && put_map())
	return;
    COMPILE;
    TWOPARAMS("map");
    ONEQUOTE("map");
#endif
    prog = stk->u.lis;
    POP(stk);
    cur = stk;
    POP(stk);
    switch (cur->op) {
    case LIST_:
	for (cur = cur->u.lis; cur; cur = cur->next) {
	    if (OUTSIDE)
		back = backup();
	    else
		CONDITION;
	    save = stk;
	    DUPLICATE(cur);
	    exeterm(prog);
#ifndef NCHECK
	    if (stk == memory)
		execerror("non-empty stack", "map");
#endif
	    if (!root)
		last = root = heapnode(stk->op, stk->u.ptr, 0);
	    else
		last = last->next = heapnode(stk->op, stk->u.ptr, 0);
	    stk = save;
	    if (OUTSIDE)
		restore(back);
	    else
		RELEASE;
	}
	PUSH(LIST_, root);
	break;
    case STRING_:
	str = cur->u.str;
	for (ptr = GC_strdup(str); *str; str++) {
	    if (OUTSIDE)
		back = backup();
	    else
		CONDITION;
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    ptr[i++] = stk->u.num;
	    stk = save;
	    if (OUTSIDE)
		restore(back);
	    else
		RELEASE;
	}
	ptr[i] = 0;
	PUSH(STRING_, ptr);
	break;
    case SET_:
	set = cur->u.set;
	for (zet = 0; i < SETSIZE_; i++)
	    if (set & (1 << i)) {
		if (OUTSIDE)
		    back = backup();
		else
		    CONDITION;
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		zet |= 1 << stk->u.num;
		stk = save;
		if (OUTSIDE)
		    restore(back);
		else
		    RELEASE;
	    }
	PUSH(SET_, zet);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("map");
#endif
    }
}
