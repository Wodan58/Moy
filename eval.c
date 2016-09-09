/*
    module  : eval.c
    version : 1.2
    date    : 09/09/16
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"
#include "globals1.h"
#include "compile.h"

#define P(x)		utstring_printf(str, x)
#define Q(x, y)		utstring_printf(str, x, y)

static UT_string *declhdr, *program, *library;

void EvalPrintTerm(Node *root, UT_string *str);

/*
    Evaluate must be present for all builtins that use exeterm
*/
int evaluate(Node *cur)
{
    int list;
    Entry *sym;
    UT_string *str;
    short op, changed = 0;
    Node *first, *second, *third, *fourth;

    if (!cur)
	return changed;
    if (cur->op == USR_) {
	sym = cur->u.ent;
	if (sym->u.body) {
	    if (!sym->is_used) {
		cur->op = changed = sym->is_used = 1;
		cur->next = concat(copy(sym->u.body), cur->next);
	    } else if (!sym->uniq)
		sym->uniq = ++identifier;
	}
	return changed;
    }
    op = cur->op + FALSE - FALSE_;
    switch (op) {
    case BINREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "binrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void binrec_%d();", my_ident = ++identifier);
	Q("binrec_%d();", my_ident);
	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = first->next;

	utstring_new(str);
	Q("void binrec_%d()", my_ident);
	P("{ int num; Node node, *save = stk; CONDITION;");
	EvalPrintTerm(first->u.lis, str);
	P("num = stk->u.num; RELEASE; stk = save; if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	P("node = *stk; POP(stk);");
	Q("binrec_%d();", my_ident);
	P("DUPLICATE(&node);");
	Q("binrec_%d();", my_ident);
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    } 
    case CASE:
#ifdef TRACE
	fprintf(stderr, "case\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int num = 0; for (;;) {");
	for (first = reverse(copy(fourth->u.lis)); first && first->next;
		first = first->next) {
	    list = PrintFirstList(first->u.lis, str);
	    Q("if (!Compare(N%d, stk, &error) && !error) {", list);
	    P("POP(stk);");
	    second = reverse(copy(first->u.lis));
	    EvalPrintTerm(reverse(copy(second->next)), str);
	    P("num = 1; break; }");
	}
	P("break; } if (!num) {");
	EvalPrintTerm(first->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case I:
    case APP1:
#ifdef TRACE
	fprintf(stderr, "i\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	EvalPrintTerm(fourth->u.lis, str);

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case X:
#ifdef TRACE
	fprintf(stderr, "x\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	PrintFactor(fourth, str);
	P("x_();");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case DIP:
#ifdef TRACE
	fprintf(stderr, "dip\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node save = *stk; POP(stk);");
	EvalPrintTerm(fourth->u.lis, str);
	P("DUPLICATE(&save); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case CONSTRUCT:
#ifdef TRACE
	fprintf(stderr, "construct\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *save, *root = stk; inside_condition++;");
	EvalPrintTerm(third->u.lis, str);
	P("save = stk;");
	for (first = reverse(copy(fourth->u.lis)); first; first = first->next) {
	    P("stk = save;");
	    EvalPrintTerm(first->u.lis, str);
	    P("root = newnode(stk->op, stk->u.ptr, root);");
	}
	P("inside_condition--; stk = root; }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case NULLARY:
#ifdef TRACE
	fprintf(stderr, "nullary\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *top = stk, *node; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--;");
	P("if (!stk) execerror(\"value to push\", \"nullary\");");
	P("node = stk; stk = top; DUPLICATE(node); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case UNARY:
#ifdef TRACE
	fprintf(stderr, "unary\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *top = stk->next, *node; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--;");
	P("if (!stk) execerror(\"value to push\", \"unary\");");
	P("node = stk; stk = top; DUPLICATE(node); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case UNARY2:
#ifdef TRACE
	fprintf(stderr, "unary2\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *parm = stk, *save, *result[2];");
	P("POP(stk); save = stk->next; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[0] = stk; stk = save; DUPLICATE(parm);");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--; result[1] = stk; stk = save;");
	P("DUPLICATE(result[0]); DUPLICATE(result[1]); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case UNARY3:
#ifdef TRACE
	fprintf(stderr, "unary3\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *first, *second = stk, *save, *result[3]; POP(stk);");
	P("first = stk; POP(stk); save = stk->next; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[0] = stk; stk = save; DUPLICATE(first);");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[1] = stk; stk = save; DUPLICATE(second);");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--; result[2] = stk; stk = save;");
	P("DUPLICATE(result[0]); DUPLICATE(result[1]);");
	P("DUPLICATE(result[2]); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case UNARY4:
#ifdef TRACE
	fprintf(stderr, "unary4\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *first, *second, *third = stk, *save, *result[4];");
	P("POP(stk); second = stk; POP(stk); first = stk; POP(stk);");
	P("save = stk->next; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[0] = stk; stk = save; DUPLICATE(first);");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[1] = stk; stk = save; DUPLICATE(second);");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[2] = stk; stk = save; DUPLICATE(third);");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--; result[3] = stk; stk = save;");
	P("DUPLICATE(result[0]); DUPLICATE(result[1]);");
	P("DUPLICATE(result[2]); DUPLICATE(result[3]); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case BINARY:
#ifdef TRACE
	fprintf(stderr, "binary\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *top = stk->next->next, *node; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--;");
	P("if (!stk) execerror(\"value to push\", \"binary\");");
	P("node = stk; stk = top; DUPLICATE(node); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case TERNARY:
#ifdef TRACE
	fprintf(stderr, "ternary\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *top = stk->next->next->next,*node; inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--;");
	P("if (!stk) execerror(\"value to push\", \"ternary\");");
	P("node = stk; stk = top; DUPLICATE(node); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case CLEAVE:
#ifdef TRACE
	fprintf(stderr, "cleave\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *result[2], *save = stk; inside_condition++;");
	EvalPrintTerm(third->u.lis, str);
	P("result[0] = stk; stk = save;");
	EvalPrintTerm(fourth->u.lis, str);
	P("result[1] = stk; stk = save; POP(stk);");
	P("DUPLICATE(result[0]); DUPLICATE(result[1]); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case BRANCH:
#ifdef TRACE
	fprintf(stderr, "branch\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int num = stk->u.num; POP(stk); if (num) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFTE:
#ifdef TRACE
	fprintf(stderr, "ifte\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int num; Node *save = stk; CONDITION;");
	EvalPrintTerm(second->u.lis, str);
	P("num = stk->u.num; RELEASE; stk = save; if (num) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = second->next;
	break;

    case IFLIST:
#ifdef TRACE
	fprintf(stderr, "iflist\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == LIST_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFINTEGER:
#ifdef TRACE
	fprintf(stderr, "ifinteger\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == INTEGER_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFCHAR:
#ifdef TRACE
	fprintf(stderr, "ifchar\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == CHAR_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFLOGICAL:
#ifdef TRACE
	fprintf(stderr, "iflogical\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == BOOLEAN_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFSET:
#ifdef TRACE
	fprintf(stderr, "ifset\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == SET_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFSTRING:
#ifdef TRACE
	fprintf(stderr, "ifstring\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == STRING_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFFLOAT:
#ifdef TRACE
	fprintf(stderr, "iffloat\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == FLOAT_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case IFFILE:
#ifdef TRACE
	fprintf(stderr, "iffile\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("if (stk->op == FILE_) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("}");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case COND:
#ifdef TRACE
	fprintf(stderr, "cond\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int num = 0; Node *save = stk; CONDITION; for (;;) {");
	for (first = reverse(copy(fourth->u.lis)); first && first->next;
		first = first->next) {
	    P("stk = save;");
	    second = reverse(copy(first->u.lis));
	    EvalPrintTerm(second->u.lis, str);
	    P("if ((num = stk->u.num) != 0) { RELEASE; stk = save;");
	    EvalPrintTerm(reverse(copy(second->next)), str);
	    P(" break; }");
	}
	P("break; } if (!num) { RELEASE; stk = save;");
	EvalPrintTerm(first->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case WHILE:
#ifdef TRACE
	fprintf(stderr, "while\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int num; Node *save; for (;;) { save = stk; CONDITION;");
	EvalPrintTerm(third->u.lis, str);
	P("num = stk->u.num; RELEASE; stk = save; if (!num) break;");
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case LINREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "linrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void linrec_%d();", my_ident = ++identifier);
	Q("linrec_%d();", my_ident);
	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = first->next;

	utstring_new(str);
	Q("void linrec_%d()", my_ident);
	P("{ int num; Node *save = stk; CONDITION;");
	EvalPrintTerm(first->u.lis, str);
	P("num = stk->u.num; RELEASE; stk = save; if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	Q("linrec_%d();", my_ident);
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }
    case TAILREC:
#ifdef TRACE
	fprintf(stderr, "tailrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void tailrec_%d();", ++identifier);
	Q("tailrec_%d();", identifier);
	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = second->next;

	utstring_new(str);
	Q("void tailrec_%d()", identifier);
	P("{ int num; Node *save; tailrec: save = stk; CONDITION;");
	EvalPrintTerm(second->u.lis, str);
	P("num = stk->u.num; RELEASE; stk = save; if (num) {");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(fourth->u.lis, str);
	P("goto tailrec; } }");
	utstring_printf(library, "%s", utstring_body(str));
	break;

    case GENREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "genrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("cons_(); cons_(); cons_();");
	Q("void genrec_%d();", my_ident = ++identifier);
	Q("genrec_%d();", my_ident);
	cur->op = 0;
	cur->u.str = utstring_body(str);

	utstring_new(str);
	Q("void genrec_%d()", my_ident);
	P("{ int num; Node *save; POP(stk); save = stk; CONDITION;");
	EvalPrintTerm(first->u.lis, str);
	P("num = stk->u.num; RELEASE; stk = save; if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	PrintFactor(first, str);
	PrintFactor(second, str);
	PrintFactor(third, str);
	PrintFactor(fourth, str);
	P("cons_(); cons_(); cons_();");
	Q("PUSH(LIST_, newnode(ANON_FUNCT_, genrec_%d, 0)); cons_();",
		my_ident);
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }    
    case CONDLINREC:
    case CONDNESTREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "condnestrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void condnestrec_%d();", my_ident = ++identifier);
	Q("condnestrec_%d();", my_ident);
	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;

	utstring_new(str);
	Q("void condnestrec_%d() { Node *save = stk; CONDITION;", my_ident);
	first = reverse(copy(fourth->u.lis));
	for (; first && first->next; first = first->next) {
	    P("stk = save;");
	    second = reverse(copy(first->u.lis));
	    EvalPrintTerm(second->u.lis, str);
	    P("if (stk->u.num) { RELEASE; stk = save;");
	    second = second->next;
	    EvalPrintTerm(second->u.lis, str);
	    while ((second = second->next) != 0) {
		Q("condnestrec_%d();", my_ident);
		EvalPrintTerm(second->u.lis, str);
	    }
	    P("return; }");
	}
	P("RELEASE; stk = save;");
	first = reverse(copy(first->u.lis));
	EvalPrintTerm(first->u.lis, str);
	while ((first = first->next) != 0) {
	    Q("condnestrec_%d();", my_ident);
	    EvalPrintTerm(first->u.lis, str);
	}
	P("}");
	utstring_printf(library, "%s", utstring_body(str));
	break;

    case STEP:
#ifdef TRACE
	fprintf(stderr, "step\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *data, *cur; char *str; int i; long_t set;");
	P("data = stk; POP(stk); switch (data->op) { case LIST_:");
	P("for (cur = data->u.lis; cur; cur = cur->next) {");
	P("DUPLICATE(cur);");
	EvalPrintTerm(fourth->u.lis, str);
	P("} break; case STRING_:");
	P("for (str = data->u.str; str && *str; str++) {");
	P("PUSH(CHAR_, (long_t)*str);");
	EvalPrintTerm(fourth->u.lis, str);
	P("} break; case SET_: set = data->u.set;");
	P("for (i = 0; i < _SETSIZE_; i++)");
	P("if (set & (1 << i)) { PUSH(INTEGER_, (long_t)i);");
	EvalPrintTerm(fourth->u.lis, str);
	P("} break; default: execerror(\"aggregate parameter\",\"step\"); } }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case MAP:
#ifdef TRACE
	fprintf(stderr, "map\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *cur, *root = 0, *last = 0, *data, *save;");
	P("char *str, *res; int i = 0, num; long_t set, zet = 0;");
	P("data = stk; POP(stk); save = stk; switch (data->op) {");
	P("case LIST_: for (cur = data->u.lis; cur; cur = cur->next) {");
	P("stk = save; inside_condition++; DUPLICATE(cur);");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--;");
	P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	P("if (!root) last = root = newnode(stk->op, stk->u.ptr, 0);");
	P("else last = last->next = newnode(stk->op, stk->u.ptr, 0);");
	P("} stk = save; PUSH(LIST_, root); break; case STRING_:");
	P("res = strdup(data->u.str);");
	P("for (str = data->u.str; str && *str; str++) {");
	P("stk = save; CONDITION; PUSH(CHAR_, (long_t)*str);");
	EvalPrintTerm(fourth->u.lis, str);
	P("num = stk->u.num; RELEASE;");
	P("res[i++] = num; } stk = save; PUSH(STRING_, res); break;");
	P("case SET_: set = data->u.set;");
	P("for (i = 0; i < _SETSIZE_; i++) if (set & (1 << i)) {");
	P("stk = save; CONDITION; PUSH(INTEGER_, (long_t)i);");
	EvalPrintTerm(fourth->u.lis, str);
	P("num = stk->u.num; RELEASE;");
	P("zet |= 1 << num; } stk = save; PUSH(SET_, (long_t)zet); break;");
	P("default: execerror(\"aggregate parameter\", \"map\"); } }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case TIMES:
#ifdef TRACE
	fprintf(stderr, "times\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int i, num = stk->u.num; POP(stk);");
	P("for (i = 0; i < num; i++) {");
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case INFRA:
#ifdef TRACE
	fprintf(stderr, "infra\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *prog, *save = stk->next; stk = stk->u.lis;");
	P("inside_condition++;");
	EvalPrintTerm(fourth->u.lis, str);
	P("inside_condition--;");
	P("prog = stk; stk = save; PUSH(LIST_, prog); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case PRIMREC:
#ifdef TRACE
	fprintf(stderr, "primrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ int i, num = 0; Node *data, *cur; char *str; long_t set;");
	P("data = stk; POP(stk); switch (data->op) { case LIST_:");
	P("for (cur = data->u.lis; cur; cur = cur->next, num++)");
	P("DUPLICATE(cur); break; case STRING_:");
	P("for (str = data->u.str; str && *str; str++, num++)");
	P("PUSH(CHAR_, (long_t)*str); break; case SET_: set = data->u.set;");
	P("for (i = 0; i < _SETSIZE_; i++) if (set & (1 << i)) {");
	P("PUSH(INTEGER_, (long_t)i); num++; } break; case INTEGER_:");
	P("for (i = num = data->u.num; i > 0; i--)");
	P("PUSH(INTEGER_, (long_t)i); break; default:");
	P("execerror(\"different type\", \"primrec\"); }");
	EvalPrintTerm(third->u.lis, str);
	P("for (i = 0; i < num; i++) {");
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = third->next;
	break;

    case FILTER:
#ifdef TRACE
	fprintf(stderr, "filter\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *cur = stk, *root = 0, *last, *save; int i, num;");
	P("char *str, *res; long_t set, zet = 0; POP(stk); save = stk;");
	P("switch (cur->op) { case LIST_:"); P("for (cur = cur->u.lis;");
	P("cur; cur = cur->next) {");
	P("CONDITION; stk = newnode(cur->op, cur->u.ptr, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("num = stk->u.num; RELEASE; if (num) {");
	P("if (!root) last = root = newnode(cur->op, cur->u.ptr, 0);");
	P("else last = last->next = newnode(cur->op, cur->u.ptr, 0);");
	P("} } stk = save; PUSH(LIST_, root); break; case STRING_:");
	P("str = cur->u.str; res = strdup(str); CONDITION;");
	P("for (i = 0; str && *str; str++) { stk = CHAR_NEWNODE(*str, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) res[i++] = *str; } RELEASE; res[i] = 0;");
	P("stk = save; PUSH(STRING_, res); break; case SET_:");
	P("set = cur->u.set; CONDITION; for (i = 0; i < _SETSIZE_; i++)");
	P("if (set & (1 << i)) { stk = INTEGER_NEWNODE(i, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) zet |= 1 << i; } RELEASE;");
	P("stk = save; PUSH(SET_, (long_t)zet); break;");
	P("default: execerror(\"valid aggregate\", \"filter\"); } }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case SPLIT:
#ifdef TRACE
	fprintf(stderr, "split\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *cur = stk, *root = 0, *head = 0, *last, *tail, *save;");
	P("int i, j, num; char *str, *res, *rez; long_t set, zet = 0,");
	P("zed = 0; POP(stk); save = stk; switch (cur->op) { case LIST_:");
	P("for (cur = cur->u.lis; cur; cur = cur->next) {");
	P("CONDITION; stk = newnode(cur->op, cur->u.ptr, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("num = stk->u.num; RELEASE; if (num) {");
	P("if (!root) last = root = newnode(cur->op, cur->u.ptr, 0);");
	P("else last = last->next = newnode(cur->op, cur->u.ptr, 0);");
	P("} else {");
	P("if (!head) tail = head = newnode(cur->op, cur->u.ptr, 0);");
	P("else tail = tail->next = newnode(cur->op, cur->u.ptr, 0);");
	P("} } stk = save; PUSH(LIST_, root); PUSH(LIST_, head);");
	P("break; case STRING_: str = cur->u.str; res = strdup(str);");
	P("rez = strdup(str); CONDITION;");
	P("for (j = i = 0; str && *str; str++) {");
	P("stk = CHAR_NEWNODE(*str, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) res[i++] = *str; else rez[j++] = *str; }");
	P("RELEASE; res[i] = 0; rez[j] = 0; stk = save; PUSH(STRING_, res);");
	P("PUSH(STRING_, rez); break; case SET_: set = cur->u.set; CONDITION;");
	P("for (i = 0; i < _SETSIZE_; i++) if (set & (1 << i)) {");
	P("stk = INTEGER_NEWNODE(i, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) zet |= 1 << i; else zed |= 1 << i; }");
	P("RELEASE; stk = save; PUSH(SET_, (long_t)zet); break; default:");
	P("execerror(\"valid aggregate\", \"split\"); } }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case SOME:
#ifdef TRACE
	fprintf(stderr, "some\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *cur = stk, *save; int i, num = 0; char *str; long_t set;");
	P("POP(stk); save = stk; CONDITION; switch (cur->op) { case LIST_:");
	P("for (cur = cur->u.lis; cur; cur = cur->next) {");
	P("stk = newnode(cur->op, cur->u.ptr, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) { num = 1; break; } } break; case STRING_:");
	P("for (str = cur->u.str; str && *str; str++) {");
	P("stk = CHAR_NEWNODE(*str, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) { num = 1; break; } } break; case SET_:");
	P("set = cur->u.set;");
	P("for (i = 0; i < _SETSIZE_; i++) if (set & (1 << i)) {");
	P("stk = INTEGER_NEWNODE(i, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) { num = 1; break; } } break;");
	P("default: execerror(\"valid aggregate\", \"some\"); }");
	P("RELEASE; stk = save; PUSH(BOOLEAN_, (long_t)num); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;

    case ALL:
#ifdef TRACE
	fprintf(stderr, "all\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	P("{ Node *cur = stk, *save; int i, num = 1; char *str; long_t set;");
	P("POP(stk); save = stk; CONDITION; switch (cur->op) {");
	P("case LIST_: for (cur = cur->u.lis; cur; cur = cur->next) {");
	P("stk = newnode(cur->op, cur->u.ptr, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) { num = 0; break; } } break; case STRING_:");
	P("for (str = cur->u.str; str && *str; str++) {");
	P("stk = CHAR_NEWNODE(*str, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) { num = 0; break; } } break; case SET_:");
	P("set = cur->u.set;");
	P("for (i = 0; i < SETSIZE; i++) if (set & (1 << i)) {");
	P("stk = INTEGER_NEWNODE(i, save);");
	EvalPrintTerm(fourth->u.lis, str);
	P("if (stk->u.num) { num = 0; break; } } break;");
	P("default: execerror(\"valid aggregate\", \"all\"); }");
	P("RELEASE; stk = save; PUSH(BOOLEAN_, (long_t)num); }");

	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;
	break;
    }
    case TREESTEP:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "treestep\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void treestep_%d(Node *item);", my_ident = ++identifier);
	Q("{ Node *item = stk; POP(stk); treestep_%d(item); }", my_ident);
	cur->op = 0;
	cur->u.str = utstring_body(str);
	cur->next = fourth->next;

	utstring_new(str);
	Q("void treestep_%d(Node *item) { Node *cur;", my_ident);
	P("if (item->op != LIST_) { DUPLICATE(item);");
	EvalPrintTerm(fourth->u.lis, str);
	P("} else for (cur = item->u.lis; cur; cur = cur->next)");
	Q("treestep_%d(cur); }", my_ident);
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }
    case TREEREC:
#ifdef TRACE
	fprintf(stderr, "treerec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void treerec_%d();", ++identifier);
	Q("cons_(); treerec_%d();", identifier);
	cur->op = 0;
	cur->u.str = utstring_body(str);

	utstring_new(str);
	Q("void treerec_%d() {", identifier);
	P("if (stk->next->op == LIST_) {");
	Q("PUSH(LIST_, newnode(ANON_FUNCT_, treerec_%d, 0)); cons_();",
		identifier);
	EvalPrintTerm(fourth->u.lis, str);
	P("} else { POP(stk);");
	EvalPrintTerm(third->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;

    case TREEGENREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "treegenrec\n");
#endif
	if ((fourth = cur->next) == 0)
	    break;
	if ((third = fourth->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if (fourth->op != LIST_)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;

	changed = 1;
	utstring_new(str);
	Q("void treegenrec_%d();", my_ident = ++identifier);
	Q("cons_(); cons_(); treegenrec_%d();", my_ident);
	cur->op = 0;
	cur->u.str = utstring_body(str);

	utstring_new(str);
	Q("void treegenrec_%d() {", my_ident);
	P("Node *save = stk; POP(stk); if (stk->op == LIST_) {");
	EvalPrintTerm(third->u.lis, str);
	P("DUPLICATE(save);");
	Q("PUSH(LIST_, newnode(ANON_FUNCT_, treegenrec_%d, 0)); cons_();",
		my_ident);
	EvalPrintTerm(fourth->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }
    }
    return changed;
}

/*
    Look for replacements until no more replacements can be done
*/
void EvalPrintTerm(Node *root, UT_string *str)
{
    Node *cur;
    short changed;

    root = copy(root);
    do {
#ifdef TRACE
	fprintf(stderr, "Compiling: ");
	writeterm(root, stderr);
	fputc('\n', stderr);
#endif
	for (changed = 0, cur = root; cur; cur = cur->next)
	    changed |= evaluate(cur);
    } while (changed);
    PrintTerm(reverse(root), str);
}

char *scramble(char *str)
{
    int i;
    char *ptr = str;

    for (i = 0; str[i]; i++)
	if (isalnum(str[i]) || str[i] == '-' || str[i] == '_')
	    ;
	else
	    return "op";
    if (strchr(ptr, '-')) {
	ptr = strdup(ptr);
	for (i = 0; ptr[i]; i++)
	    if (ptr[i] == '-')
		ptr[i] = '_';
    }
    return ptr;
}

void compilelib()
{
    char *name;
    Entry *sym;
    int changed;
    UT_string *str;

    do
	for (changed = 0, sym = symtab; sym < symtabindex; sym++)
	    if (!sym->mark && sym->uniq) {
		sym->mark = changed = 1;
		utstring_new(str);
		EvalPrintTerm(sym->u.body, str);
		name = scramble(sym->name);
		utstring_printf(declhdr, "void %s_%d(void);\n",
				name, sym->uniq);
		utstring_printf(library, "void %s_%d(void) {\n%s}\n\n",
				name, sym->uniq, utstring_body(str));
	    }
    while (changed);
}

void exitcompile(void)
{
    compilelib();
    time_t t = time(0);
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#include \"runtime.h\"\n\n");
    printf("%s\n", utstring_body(declhdr));
    printf("int joy_main() {\n");
    printf("stk = &memory[MEMORYMAX];\n");
    printf("%sreturn 0; }\n\n", utstring_body(program));
    printf("%s", utstring_body(library));
    fflush(stdout);
}

/*
    Compile a term - instead of being executed, commands are printed.
*/
void compile(Node *node)
{
    static short init;
    Entry *sym;

    if (!init) {
	init = 1;
	atexit(exitcompile);
	utstring_new(declhdr);
	utstring_new(program);
	utstring_new(library);
    }
    EvalPrintTerm(node, program);
    utstring_printf(program, "writestack();\n");
    for (sym = symtab; sym < symtabindex; sym++)
	sym->is_used = 0;
}
