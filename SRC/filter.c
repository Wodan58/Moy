/*
    module  : filter.c
    version : 1.12
    date    : 03/12/17
*/
#include "runtime.h"

#ifndef NCHECK
int put_filter(void)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* FILTER */");
    fprintf(outfp, "char *str, *yes_str;");
    fprintf(outfp, "unsigned i, j, yes = 0;");
    fprintf(outfp, "ulong_t set, yes_set = 0;");
    fprintf(outfp, "Node *list, *node, *temp, *yes_list, *tmp;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "CONDITION; save = stk; DUPLICATE(list);");
    evaluate(prog);
    fprintf(outfp, "if (stk->u.num) { if (!root)");
    fprintf(outfp, "cur = root = heapnode(list->op, list->u.ptr, 0); else ");
    fprintf(outfp, "cur = cur->next = heapnode(list->op, list->u.ptr, 0);");
    fprintf(outfp, "} stk = save; RELEASE; }");
    fprintf(outfp, "PUSH(LIST_, root); break;");
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "yes_str = strdup(str);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "CONDITION; save = stk; PUSH(CHAR_, (long_t)*str);");
    evaluate(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "yes_str[yes++] = *str;");
    fprintf(outfp, "} stk = save; RELEASE; yes_str[yes] = 0;");
    fprintf(outfp, "PUSH(STRING_, yes_str); break;");
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & (1 << i)) {");
    fprintf(outfp, "CONDITION; save = stk; PUSH(INTEGER_, i);");
    evaluate(prog);
    fprintf(outfp, "if (stk->u.num)");
    fprintf(outfp, "yes_set |= 1 << i;");
    fprintf(outfp, "stk = save; RELEASE;");
    fprintf(outfp, "} PUSH(SET_, yes_set); break; } }");
    return 1;
}
#endif

/*
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
PRIVATE void do_filter(void)
{
    int i = 0;
    char *str, *ptr;
    ulong_t set, zet = 0;
    Node *prog, *save, *list, *root = 0, *cur;

#ifndef NCHECK
    if (optimizing && put_filter())
	return;
    COMPILE;
    TWOPARAMS("filter");
    ONEQUOTE("filter");
#endif
    prog = stk->u.lis;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	list = stk->u.lis;
	POP(stk);
	for (; list; list = list->next) {
	    CONDITION;
	    save = stk;
	    DUPLICATE(list);
	    exeterm(prog);
	    if (stk->u.num) {
		if (!root)
		    cur = root = heapnode(list->op, list->u.ptr, 0);
		else
		    cur = cur->next = heapnode(list->op, list->u.ptr, 0);
	    }
	    stk = save;
	    RELEASE;
	}
	PUSH(LIST_, root);
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	for (ptr = GC_strdup(str); *str; str++) {
	    CONDITION;
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    if (stk->u.num)
		ptr[i++] = *str;
	    stk = save;
	    RELEASE;
	}
	ptr[i] = 0;
	PUSH(STRING_, ptr);
	break;
    case SET_:
	set = stk->u.set;
	POP(stk);
	for (i = 0; i < SETSIZE_; i++)
	    if (set & (1 << i)) {
		CONDITION;
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		if (stk->u.num)
		    zet |= 1 << i;
		stk = save;
		RELEASE;
	    }
	PUSH(SET_, zet);
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("filter");
#endif
    }
}
