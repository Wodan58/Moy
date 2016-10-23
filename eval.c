/*
    module  : eval.c
    version : 1.17
    date    : 10/21/16
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"
#include "globals1.h"
#include "compile.h"

// #define DEBUG
// #define TRACE

#define P(x)		utstring_printf(str, x)
#define Q(x, y)		utstring_printf(str, x, y)
#define R(x, y, z)	utstring_printf(str, x, y, z)

void EvalPrintTerm(Node *root, UT_string *str);

enum {
    t_BOOLEAN = BOOLEAN_ + FALSE - FALSE_,
    t_CHAR,
    t_INTEGER,
    t_FLOAT,
    t_USR,
    t_SYMBOL,
    t_STRING,
    t_SET,
    t_LIST,
    t_FILE,
    t_ANON_FUNCT
};

#ifdef DEBUG
static char *datatype[] = {
    "BOOLEAN",
    "CHAR",
    "INTEGER",
    "FLOAT",
    "USR",
    "SYMBOL",
    "STRING",
    "SET",
    "LIST",
    "FILE",
    "ANON_FUNCT"
};
#endif

/*
    optimize must be present for all builtins that use exeterm
*/
void optimize(Node *node, UT_string *library)
{
#ifdef ARITY
    int d;
#endif
    int list, op;
    UT_string *str;
    Node *cur, *first, *second, *third, *fourth;

    if (!node || !node->op)
	return;
    /* t_USR = 263 + 275 - 12 = 526 */
    op = node->op + FALSE - FALSE_;

#ifdef DEBUG
    if (node->op <= 231)
	fprintf(stderr, "eval: %s\n", optable[node->op].name);
    else if (op >= t_BOOLEAN && op <= t_ANON_FUNCT)
	fprintf(stderr, "eval: %s\n", datatype[op - t_BOOLEAN]);
    else
	fprintf(stderr, "eval: %d\n", node->op);
#endif

    switch (op) {
    case t_USR:
	utstring_new(str);
	Entry *sym = node->u.ent;
	if (!sym->u.body)
	    Q("PUSH(SYMBOL_, \"%s\");", sym->name);
	else {
	    if (!sym->uniq)
		sym->uniq = ++identifier;
	    char *name = scramble(sym->name);
	    if (node->unmark)
		R("PUSH(ANON_FUNCT_, %s_%d);", name, sym->uniq);
	    else {
		R("void %s_%d();", name, sym->uniq);
		R("%s_%d();", name, sym->uniq);
	    }
	}
	node->op = 0;
	node->u.str = utstring_body(str);
	break;

    case BINREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "binrec\n");
#endif
	if ((fourth = node->next) == 0)
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

	utstring_new(str);
	Q("void binrec_%d();", my_ident = ++identifier);
	Q("binrec_%d();", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;

	utstring_new(str);
	Q("void binrec_%d()", my_ident);
	P("{ int num; Node *save, temp;");
	P("save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("num = stk->u.num;");
	P("stk = save;");
	P("if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	P("temp = *stk; POP(stk);");
	Q("binrec_%d();", my_ident);
	P("DUPLICATE(&temp);");
	Q("binrec_%d();", my_ident);
	EvalPrintTerm(fourth->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }

    case CASE:
    {
#ifdef TRACE
	fprintf(stderr, "case\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ int num = 0; for (;;) {");
	for (cur = first->u.lis; cur && cur->next; cur = cur->next) {
	    list = PrintFirstList(cur->u.lis, str);
	    Q("if (!Compare(L%d, stk, &error) && !error) { POP(stk);", list);
	    EvalPrintTerm(cur->u.lis->next, str);
	    P("num = 1; break; }");
	}
	P("break; } if (!num) {");
	EvalPrintTerm(cur->u.lis, str);
	P("} }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case I:
    {
#ifdef TRACE
	fprintf(stderr, "i\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	EvalPrintTerm(first->u.lis, str);

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case X:
    {
#ifdef TRACE
	fprintf(stderr, "x\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	PrintFactor(first, str);
	P("x_();");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case DIP:
    {
#ifdef TRACE
	fprintf(stderr, "dip\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node temp = *stk; POP(stk);");
	EvalPrintTerm(first->u.lis, str);
	P("DUPLICATE(&temp); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case CONSTRUCT:
    {
#ifdef TRACE
	fprintf(stderr, "construct\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node *root = 0, *save[2];");
	P("save[0] = stk;");
	EvalPrintTerm(first->u.lis, str);
	for (cur = second->u.lis; cur; cur = cur->next) {
	    P("save[1] = stk;");
#ifdef ARITY
	    if ((d = arity(cur->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    EvalPrintTerm(cur->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("root = heapnode(stk->op, stk->u.ptr, root);");
	    P("stk = save[1];");
	}
	P("stk = save[0];");
	P("while (root) { DUPLICATE(root); root = root->next; } }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case NULLARY:
    {
#ifdef TRACE
	fprintf(stderr, "nullary\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node *top, *save;");
	P("top = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("if (!stk) execerror(\"value to push\", \"nullary\");");
	P("save = stk; stk = top; DUPLICATE(save); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case UNARY:
    {
#ifdef TRACE
	fprintf(stderr, "unary\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node *top, *save;");
	P("top = stk->next;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("if (!stk) execerror(\"value to push\", \"unary\");");
	P("save = stk; stk = top; DUPLICATE(save); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case UNARY2:
    {
#ifdef TRACE
	fprintf(stderr, "unary2\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node temp, *top, result[2];");
	P("temp = *stk; POP(stk); top = stk->next;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[0] = *stk; stk = top; DUPLICATE(&temp);");
#ifdef ARITY
	if (d)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[1] = *stk; stk = top;");
	P("DUPLICATE(&result[0]); DUPLICATE(&result[1]); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case UNARY3:
    {
#ifdef TRACE
	fprintf(stderr, "unary3\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node first, second, *top, result[3];");
	P("second = *stk; POP(stk); first = *stk; POP(stk); top = stk->next;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[0] = *stk; stk = top; DUPLICATE(&first);");
#ifdef ARITY
	if (d)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[1] = *stk; stk = top; DUPLICATE(&second);");
#ifdef ARITY
	if (d)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[2] = *stk; stk = top; DUPLICATE(&result[0]);");
	P("DUPLICATE(&result[1]); DUPLICATE(&result[2]); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case UNARY4:
    {
#ifdef TRACE
	fprintf(stderr, "unary4\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node first, second, third, *top, result[4];");
	P("third = *stk; POP(stk); second = *stk; POP(stk);");
	P("first = *stk; POP(stk); top = stk->next;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[0] = *stk; stk = top; DUPLICATE(&first);");
#ifdef ARITY
	if (d)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[1] = *stk; stk = top; DUPLICATE(&second);");
#ifdef ARITY
	if (d)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[2] = *stk; stk = top; DUPLICATE(&third);");
#ifdef ARITY
	if (d)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[3] = *stk; stk = top; DUPLICATE(&result[0]);");
	P("DUPLICATE(&result[1]); DUPLICATE(&result[2]);");
	P("DUPLICATE(&result[3]); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case BINARY:
    {
#ifdef TRACE
	fprintf(stderr, "binary\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node *top, *save;");
	P("top = stk->next->next;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("if (!stk) execerror(\"value to push\", \"binary\");");
	P("save = stk; stk = top; DUPLICATE(save); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case TERNARY:
    {
#ifdef TRACE
	fprintf(stderr, "ternary\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node *top, *save;");
	P("top = stk->next->next->next;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("if (!stk) execerror(\"value to push\", \"ternary\");");
	P("save = stk; stk = top; DUPLICATE(save); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case CLEAVE:
    {
#ifdef TRACE
	fprintf(stderr, "cleave\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node result[2], *save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[0] = *stk; stk = save;");
#ifdef ARITY
	if ((d = arity(second->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(second->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("result[1] = *stk; stk = save; POP(stk);");
	P("DUPLICATE(&result[0]); DUPLICATE(&result[1]); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case BRANCH:
    {
#ifdef TRACE
	fprintf(stderr, "branch\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ int num = stk->u.num; POP(stk); if (num) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("} }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFTE:
    {
#ifdef TRACE
	fprintf(stderr, "ifte\n");
#endif
	if ((third = node->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ int num; Node *save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("num = stk->u.num;");
	P("stk = save;");
	P("if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	P("} }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFLIST:
    {
#ifdef TRACE
	fprintf(stderr, "iflist\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == LIST_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFINTEGER:
    {
#ifdef TRACE
	fprintf(stderr, "ifinteger\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == INTEGER_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFCHAR:
    {
#ifdef TRACE
	fprintf(stderr, "ifchar\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == CHAR_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFLOGICAL:
    {
#ifdef TRACE
	fprintf(stderr, "iflogical\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == BOOLEAN_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFSET:
    {
#ifdef TRACE
	fprintf(stderr, "ifset\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == SET_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFSTRING:
    {
#ifdef TRACE
	fprintf(stderr, "ifstring\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == STRING_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFFLOAT:
    {
#ifdef TRACE
	fprintf(stderr, "iffloat\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == FLOAT_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case IFFILE:
    {
#ifdef TRACE
	fprintf(stderr, "iffile\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("if (stk->op == FILE_) {");
	EvalPrintTerm(first->u.lis, str);
	P("} else {");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case COND:
    {
#ifdef TRACE
	fprintf(stderr, "cond\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ int num = 0; Node *save; for (;;) {");
	for (cur = first->u.lis; cur && cur->next; cur = cur->next) {
	    second = cur->u.lis->u.lis;
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(second)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    EvalPrintTerm(second, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num;");
	    P("stk = save;");
	    P("if (num) {");
	    EvalPrintTerm(cur->u.lis->next, str);
	    P(" break; }");
	}
	P("break; } if (!num) {");
	EvalPrintTerm(cur->u.lis, str);
	P("} }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case WHILE:
    {
#ifdef TRACE
	fprintf(stderr, "while\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("for (;;) { int num; Node *save;");
	P("save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("num = stk->u.num;");
	P("stk = save;");
	P("if (!num) break;");
	EvalPrintTerm(second->u.lis, str);
	P("}");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case LINREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "linrec\n");
#endif
	if ((fourth = node->next) == 0)
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

	utstring_new(str);
	Q("void linrec_%d();", my_ident = ++identifier);
	Q("linrec_%d();", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;

	utstring_new(str);
	Q("void linrec_%d()", my_ident);
	P("{ int num; Node *save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("num = stk->u.num;");
	P("stk = save;");
	P("if (num) {");
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
    {
#ifdef TRACE
	fprintf(stderr, "tailrec\n");
#endif
	if ((third = node->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	Q("void tailrec_%d();", ++identifier);
	Q("tailrec_%d();", identifier);
	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;

	utstring_new(str);
	Q("void tailrec_%d()", identifier);
	P("{ int num; Node *save; tailrec: save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("num = stk->u.num;");
	P("stk = save;");
	P("if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	P("goto tailrec; } }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }

    case GENREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "genrec\n");
#endif
	if ((fourth = node->next) == 0)
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

	utstring_new(str);
	P("cons_(); cons_(); cons_();");
	Q("void genrec_%d();", my_ident = ++identifier);
	Q("genrec_%d();", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);

	utstring_new(str);
	Q("void genrec_%d()", my_ident);
	P("{ int num; Node *save; POP(stk); save = stk;");
#ifdef ARITY
	if ((d = arity(first->u.lis)) != 0)
	    Q("copy_(%d);", d);
#else
	P("CONDITION;");
#endif
	EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	P("RELEASE;");
#endif
	P("num = stk->u.num;");
	P("stk = save;");
	P("if (num) {");
	EvalPrintTerm(second->u.lis, str);
	P("} else {");
	EvalPrintTerm(third->u.lis, str);
	PrintFactor(first, str);
	PrintFactor(second, str);
	PrintFactor(third, str);
	PrintFactor(fourth, str);
	P("cons_(); cons_(); cons_();");
	Q("NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(genrec_%d, 0));", my_ident);
	P("cons_();");
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
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	Q("void condnestrec_%d();", my_ident = ++identifier);
	Q("condnestrec_%d();", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;

	utstring_new(str);
	Q("void condnestrec_%d() { int num = 0; Node *save;", my_ident);
	for (cur = first->u.lis; cur && cur->next; cur = cur->next) {
	    first = cur->u.lis;
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num;");
	    P("stk = save;");
	    P("if (num) {");
	    first = first->next;
	    EvalPrintTerm(first->u.lis, str);
	    while ((first = first->next) != 0) {
		Q("condnestrec_%d();", my_ident);
		EvalPrintTerm(first->u.lis, str);
	    }
	    P("return; }");
	}
	first = cur->u.lis;
	EvalPrintTerm(first->u.lis, str);
	while ((first = first->next) != 0) {
	    Q("condnestrec_%d();", my_ident);
	    EvalPrintTerm(first->u.lis, str);
	}
	P("}");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }

    case STEP:
    {
#ifdef TRACE
	fprintf(stderr, "step\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;
	if ((second = first->next) == 0)
	    break;

	utstring_new(str);
	if (second->op == LIST_) {
	    P("{ Node *list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
	    P("} }");
	} else if (second->op == STRING_) {
	    P("{ char *str = stk->u.str; POP(stk);");
	    P("for (; *str; str++) {");
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
	    P("} }");
	} else if (second->op == SET_) {
	    P("{ int i; long_t set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
	    P("} }");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("Node *list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
	    P("} } else if (stk->op == STRING_) {");
	    P("char *str = stk->u.str; POP(stk);");
	    P("for (; *str; str++) {");
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
	    P("} } else if (stk->op == SET_) {");
	    P("int i; long_t set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
	    P("} } else { BADAGGREGATE(\"step\"); }");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case MAP:
    {
#ifdef TRACE
	fprintf(stderr, "map\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;
	if ((second = first->next) == 0)
	    break;

	utstring_new(str);
	if (second->op == LIST_) {
	    P("{ Node *save, *list, *root = 0, *cur;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	    P("if (!root) cur = root = heapnode(stk->op, stk->u.ptr, 0);");
	    P("else cur = cur->next = heapnode(stk->op, stk->u.ptr, 0);");
	    P("stk = save; } PUSH(LIST_, root); }");
	} else if (second->op == STRING_) {
	    P("{ Node *save; int i; char *str, *result;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (i = 0, result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	    P("result[i++] = stk->u.num; stk = save; }");
	    P("result[i] = 0; PUSH(STRING_, result); }");
	} else if (second->op == SET_) {
	    P("{ Node *save; int i; long_t set, result;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (result = i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	    P("result |= 1 << stk->u.num; stk = save; }");
	    P("PUSH(SET_, result); }");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("Node *save, *list, *root = 0, *cur;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	    P("if (!root) cur = root = heapnode(stk->op, stk->u.ptr, 0);");
	    P("else cur = cur->next = heapnode(stk->op, stk->u.ptr, 0);");
	    P("stk = save; } PUSH(LIST_, root); }");
	    P("else if (stk->op == STRING_) {");
	    P("Node *save; int i; char *str, *result;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (i = 0, result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	    P("result[i++] = stk->u.num; stk = save; }");
	    P("result[i] = 0; PUSH(STRING_, result); }");
	    P("else if (stk->op == SET_) {");
	    P("Node *save; int i; long_t set, result;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (result = i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (!stk) execerror(\"non-empty stack\", \"map\");");
	    P("result |= 1 << stk->u.num; stk = save; }");
	    P("PUSH(SET_, result); }");
	    P("else {");
	    P("BADAGGREGATE(\"map\");");
	    P("}");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case TIMES:
    {
#ifdef TRACE
	fprintf(stderr, "times\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ int num = stk->u.num; POP(stk);");
	P("while (num--) {");
	EvalPrintTerm(first->u.lis, str);
	P("} }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case INFRA:
    {
#ifdef TRACE
	fprintf(stderr, "infra\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	P("{ Node *list, *save;");
	P("list = stk->u.lis; POP(stk);");
	P("save = stk2lst(); lst2stk(list);");
	EvalPrintTerm(first->u.lis, str);
	P("list = stk2lst(); lst2stk(save);");
	P("PUSH(LIST_, list); }");

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case PRIMREC:
    {
#ifdef TRACE
	fprintf(stderr, "primrec\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;
	if ((third = first->next) == 0)
	    break;

	utstring_new(str);
	if (third->op == LIST_) {
	    P("{ int num = 0; Node *list;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next, num++)");
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("}");
	} else if (third->op == STRING_) {
	    P("{ int num = 0; char *str;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (; str && *str; str++, num++)");
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("}");
	} else if (third->op == SET_) {
	    P("{ int i, num = 0; long_t set;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("PUSH(INTEGER_, i); num++; }");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("}");
	} else if (third->op == INTEGER_) {
	    P("{ int i, num = stk->u.num; POP(stk);");
	    P("for (i = num; i > 0; i--)");
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("}");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("int num = 0; Node *list;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next, num++)");
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("} else if (stk->op == STRING_) {");
	    P("int num = 0; char *str;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (; str && *str; str++, num++)");
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("} else if (stk->op == SET_) {");
	    P("int i, num = 0; long_t set;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("PUSH(INTEGER_, i); num++; }");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("} else if (stk->op == INTEGER_) {");
	    P("int i, num = stk->u.num; POP(stk);");
	    P("for (i = num; i > 0; i--)");
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
	    P("while (num--)");
	    EvalPrintTerm(second->u.lis, str);
	    P("} else {");
	    P("BADAGGREGATE(\"map\");");
	    P("}");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case FILTER:
    {
#ifdef TRACE
	fprintf(stderr, "filter\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;
	if ((second = first->next) == 0)
	    break;

	utstring_new(str);
	if (second->op == LIST_) {
	    P("{ int num = 0; Node *save, *list, *root = 0, *cur;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num) {");
	    P("if (!root) cur = root = heapnode(list->op, list->u.ptr, 0);");
	    P("else cur = cur->next = heapnode(list->op, list->u.ptr, 0); }");
	    P("} PUSH(LIST_, root); }");
	} else if (second->op == STRING_) {
	    P("{ Node *save; int i = 0; char *str, *result;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result[i++] = *str; stk = save; }");
	    P("result[i] = 0; PUSH(STRING_, result); }");
	} else if (second->op == SET_) {
	    P("{ Node *save; int i; long_t set, result = 0;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result |= 1 << i; stk = save; }");
	    P("PUSH(SET_, result); }");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("int num = 0; Node *save, *list, *root = 0, *cur;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num) {");
	    P("if (!root) cur = root = heapnode(list->op, list->u.ptr, 0);");
	    P("else cur = cur->next = heapnode(list->op, list->u.ptr, 0); }");
	    P("} PUSH(LIST_, root); }");
	    P("else if (stk->op == STRING_) {");
	    P("Node *save; int i = 0; char *str, *result;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result[i++] = *str; stk = save; }");
	    P("result[i] = 0; PUSH(STRING_, result); }");
	    P("else if (stk->op == SET_) {");
	    P("Node *save; int i; long_t set, result = 0;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result |= 1 << i; stk = save; }");
	    P("PUSH(SET_, result); }");
	    P("else {");
	    P("BADAGGREGATE(\"filter\");");
	    P("}");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case SPLIT:
    {
#ifdef TRACE
	fprintf(stderr, "split\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;
	if ((second = first->next) == 0)
	    break;

	utstring_new(str);
	if (second->op == LIST_) {
	    P("{ int num = 0; Node *save, *list, *root = 0, *cur,");
	    P("*head = 0, *tail;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num)");
	    P("if (!root) cur = root = heapnode(list->op, list->u.ptr, 0);");
	    P("else cur = cur->next = heapnode(list->op, list->u.ptr, 0);");
	    P("else if (!head)");
	    P("tail = head = heapnode(list->op, list->u.ptr, 0);");
	    P("else tail = tail->next = heapnode(list->op, list->u.ptr, 0);");
	    P("} PUSH(LIST_, root); PUSH(LIST_, head); }");
	} else if (second->op == STRING_) {
	    P("{ Node *save; int i = 0, j = 0; char *str, *result[2];");
	    P("str = stk->u.str; POP(stk); result[0] = strdup(str);");
	    P("for (result[1] = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result[0][i++] = *str;");
	    P("else result[1][j++] = *str; stk = save; }");
	    P("result[0][i] = 0; result[1][j] = 0;");
	    P("PUSH(STRING_, result[0]); PUSH(STRING_, result[1]); }");
	} else if (second->op == SET_) {
	    P("{ Node *save; int i; long_t set, result[2];");
	    P("result[0] = result[1] = 0;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result[0] |= 1 << i;");
	    P("else result[1] |= i << i; stk = save; }");
	    P("PUSH(SET_, result[0]); PUSH(SET_, result[1]); }");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("int num = 0; Node *save, *list, *root = 0, *cur,");
	    P("*head = 0, *tail;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num)");
	    P("if (!root) cur = root = heapnode(list->op, list->u.ptr, 0);");
	    P("else cur = cur->next = heapnode(list->op, list->u.ptr, 0);");
	    P("else if (!head)");
	    P("tail = head = heapnode(list->op, list->u.ptr, 0);");
	    P("else tail = tail->next = heapnode(list->op, list->u.ptr, 0);");
	    P("} PUSH(LIST_, root); PUSH(LIST_, head); }");
	    P("else if (stk->op == STRING_) {");
	    P("Node *save; int i = 0, j = 0; char *str, *result[2];");
	    P("str = stk->u.str; POP(stk); result[0] = strdup(str);");
	    P("for (result[1] = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result[0][i++] = *str;");
	    P("else result[1][j++] = *str; stk = save; }");
	    P("result[0][i] = 0; result[1][j] = 0;");
	    P("PUSH(STRING_, result[0]); PUSH(STRING_, result[1]); }");
	    P("else if (stk->op == SET_) {");
	    P("Node *save; int i; long_t set, result[2];");
	    P("result[0] = result[1] = 0;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("if (stk->u.num) result[0] |= 1 << i;");
	    P("else result[1] |= i << i; stk = save; }");
	    P("PUSH(SET_, result[0]); PUSH(SET_, result[1]); }");
	    P("else {");
	    P("BADAGGREGATE(\"split\");");
	    P("}");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case SOME:
    {
#ifdef TRACE
	fprintf(stderr, "some\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;
	if ((second = first->next) == 0)
	    break;

	utstring_new(str);
	if (second->op == LIST_) {
	    P("{ int num = 0; Node *save, *list;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	} else if (second->op == STRING_) {
	    P("{ int num = 0; Node *save; char *str;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	} else if (second->op == SET_) {
	    P("{ int num = 0; Node *save; long_t set;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; if (num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("int num = 0; Node *save, *list;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	    P("else if (stk->op == STRING_) {");
	    P("int num = 0; Node *save; char *str;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	    P("else if (stk->op == SET_) {");
	    P("int num = 0; Node *save; long_t set;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; if (num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	    P("else {");
	    P("BADAGGREGATE(\"some\");");
	    P("}");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case ALL:
    {
#ifdef TRACE
	fprintf(stderr, "all\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;
	if ((second = first->next) == 0)
	    break;

	utstring_new(str);
	if (second->op == LIST_) {
	    P("{ int num = 1; Node *save, *list;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (!num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	} else if (second->op == STRING_) {
	    P("{ int num = 1; Node *save; char *str;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (!num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	} else if (second->op == SET_) {
	    P("{ int num = 1; Node *save; long_t set;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; if (!num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	} else {
	    P("if (stk->op == LIST_) {");
	    P("int num = 1; Node *save, *list;");
	    P("list = stk->u.lis; POP(stk);");
	    P("for (; list; list = list->next) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("DUPLICATE(list);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (!num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	    P("else if (stk->op == STRING_) {");
	    P("int num = 1; Node *save; char *str;");
	    P("str = stk->u.str; POP(stk);");
	    P("for (result = strdup(str); *str; str++) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(CHAR_, *str);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; stk = save; if (!num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	    P("else if (stk->op == SET_) {");
	    P("int num = 1; Node *save; long_t set;");
	    P("set = stk->u.set; POP(stk);");
	    P("for (i = 0; i < _SETSIZE_; i++)");
	    P("if (set & (1 << i)) {");
	    P("save = stk;");
#ifdef ARITY
	    if ((d = arity(first->u.lis)) != 0)
		Q("copy_(%d);", d);
#else
	    P("CONDITION;");
#endif
	    P("PUSH(INTEGER_, i);");
	    EvalPrintTerm(first->u.lis, str);
#ifndef ARITY
	    P("RELEASE;");
#endif
	    P("num = stk->u.num; if (!num) break; }");
	    P("PUSH(BOOLEAN_, num); }");
	    P("else {");
	    P("BADAGGREGATE(\"all\");");
	    P("}");
	}

	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;
	break;
    }

    case TREESTEP:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "treestep\n");
#endif
	if ((first = node->next) == 0)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	Q("void treestep_%d(Node *item);", my_ident = ++identifier);
	Q("{ Node *item = stk; POP(stk); treestep_%d(item); }", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);
	node->next = first->next;

	utstring_new(str);
	Q("void treestep_%d(Node *item) { Node *cur;", my_ident);
	P("if (item->op != LIST_) { DUPLICATE(item);");
	EvalPrintTerm(first->u.lis, str);
	P("} else for (cur = item->u.lis; cur; cur = cur->next)");
	Q("treestep_%d(cur); }", my_ident);
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }

    case TREEREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "treerec\n");
#endif
	if ((second = node->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	Q("void treerec_%d();", my_ident = ++identifier);
	Q("cons_(); treerec_%d();", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);

	utstring_new(str);
	Q("void treerec_%d() {", my_ident);
	P("if (stk->next->op == LIST_) {");
	Q("NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerec_%d, 0));",
	my_ident);
	P("cons_();");
	EvalPrintTerm(second->u.lis, str);
	P("} else { POP(stk);");
	EvalPrintTerm(first->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    }

    case TREEGENREC:
    {
	int my_ident;
#ifdef TRACE
	fprintf(stderr, "treegenrec\n");
#endif
	if ((third = node->next) == 0)
	    break;
	if ((second = third->next) == 0)
	    break;
	if ((first = second->next) == 0)
	    break;
	if (third->op != LIST_)
	    break;
	if (second->op != LIST_)
	    break;
	if (first->op != LIST_)
	    break;

	utstring_new(str);
	Q("void treegenrec_%d();", my_ident = ++identifier);
	Q("cons_(); cons_(); treegenrec_%d();", my_ident);
	node->op = 0;
	node->u.str = utstring_body(str);

	utstring_new(str);
	Q("void treegenrec_%d() {", my_ident);
	P("Node *save = stk; POP(stk); if (stk->op == LIST_) {");
	EvalPrintTerm(second->u.lis, str);
	P("DUPLICATE(save);");
	Q("NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treegenrec_%d, 0));",
	my_ident);
	P("cons_();");
	EvalPrintTerm(third->u.lis, str);
	P("} else {");
	EvalPrintTerm(first->u.lis, str);
	P("} }");
	utstring_printf(library, "%s", utstring_body(str));
	break;
    } }
}
