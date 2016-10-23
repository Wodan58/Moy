/*
 *  module  : compile.c
 *  version : 1.19
 *  date    : 10/21/16
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"
#include "globals1.h"
#include "compile.h"
#include "builtin.h"

// #define TRACE

#ifdef TRACE
int trace = 1;
#endif

#define VALID(x)	((x) && (x)->op && !(x)->mark)
#define NUMERIC_1	(VALID(stk) && (stk->op == INTEGER_ || \
			 stk->op == FLOAT_))
#define NUMERIC_2	(VALID(stk->next) && (stk->next->op == INTEGER_ || \
			 stk->next->op == FLOAT_))
#define NUMERIC_3	(VALID(stk->next->next) && (stk->next->next->op == \
			 INTEGER_ || stk->next->next->op == FLOAT_))
#define NUMERIC_4	(VALID(stk->next->next->next) && \
			 (stk->next->next->next->op == INTEGER_ || \
			  stk->next->next->next->op == FLOAT_))
#define FLOAT_1		(VALID(stk) && stk->op == FLOAT_)
#define FLOAT_2		(VALID(stk->next) && stk->next->op == FLOAT_)
#define FLOAT_3		(VALID(stk->next->next) && \
			 stk->next->next->op == FLOAT_)
#define FLOAT_4		(VALID(stk->next->next->next) && \
			 stk->next->next->next->op == FLOAT_)
#define INTEGER_1	(VALID(stk) && stk->op == INTEGER_)
#define INTEGER_2	(VALID(stk->next) && stk->next->op == INTEGER_)
#define INTEGER_3	(VALID(stk->next->next) && \
			 stk->next->next->op == INTEGER_)
#define INTEGER_4	(VALID(stk->next->next->next) && \
			 stk->next->next->next->op == INTEGER_)
#define CHAR_1		(VALID(stk) && stk->op == CHAR_)
#define CHAR_2		(VALID(stk->next) && stk->next->op == CHAR_)
#define CHAR_3		(VALID(stk->next->next) && stk->next->next->op == CHAR_)
#define CHAR_4		(VALID(stk->next->next->next) && \
			 stk->next->next->next->op == CHAR_)
#define STRING_1	(VALID(stk) && stk->op == STRING_)
#define STRING_2	(VALID(stk->next) && stk->next->op == STRING_)
#define STRING_3	(VALID(stk->next->next) && \
			 stk->next->next->op == STRING_)
#define STRING_4	(VALID(stk->next->next->next) && \
			 stk->next->next->next->op == STRING_)
#define SET_1		(VALID(stk) && stk->op == SET_)
#define SET_2		(VALID(stk->next) && stk->next->op == SET_)
#define SET_3		(VALID(stk->next->next) && stk->next->next->op == SET_)
#define SET_4		(VALID(stk->next->next->next) && \
			 stk->next->next->next->op == SET_)
#define LIST_1		(VALID(stk) && stk->op == LIST_)
#define LIST_2		(VALID(stk->next) && stk->next->op == LIST_)
#define LIST_3		(VALID(stk->next->next) && stk->next->next->op == LIST_)
#define LIST_4		(VALID(stk->next->next->next) && \
			 stk->next->next->next->op == LIST_)
#define AGGREGATE(x)	(VALID(x) && (x)->op >= STRING_ && (x)->op <= LIST_)

UT_string *declhdr, *program, *library;

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

Node *stk2prog()
{
    Node *root = 0, *node;

    while (stk && stk != &memory[MEMORYMAX]) {
	node = getnode(1);
	*node = *stk;
	stk->unmark = stk->mark = 0;
	node->next = root;
	root = node;
	stk = stk->next;
    }
    return root;
}

int valid(Node *cur)
{
    int num = 0;

    while (cur && cur != &memory[MEMORYMAX]) {
	if (VALID(cur))
	    num++;
	else
	    break;
	cur = cur->next;
    }
    return num;
}

/*
    evaluate a term

	USR_ nodes are expanded
	evaluation starts for some builtins
	the stack is copied back to the program
	the rest is evaluated to a string
	the string is printed

	[first] first needs special treatment
*/
void evaluate(Node *node)
{
    int op;

/* USR_ nodes are expanded */
    for (node = copyterm(node); node; node = node->next) {

#ifdef TRACE
    if (trace) {
	writeterm(node, stderr);
	fprintf(stderr, " . ");
	writeterm(stk, stderr);
	fprintf(stderr, "\n");
    }
#endif

/* evaluation starts for some builtins */
	op = node->op + FALSE - FALSE_;
	switch (op) {
/* datatypes */
	case t_BOOLEAN:
	case t_CHAR:
	case t_INTEGER:
	case t_FLOAT:
	case t_SYMBOL:
	case t_STRING:
	case t_SET:
	case t_LIST:
	case t_FILE:
	case t_ANON_FUNCT:
	    DUPLICATE(node);
	    continue;

/* conversion */
	case BODY:
	    DUPLICATE(node);
	    break;

	case FORMAT:
	    if (INTEGER_1 && INTEGER_2 && CHAR_3 && NUMERIC_4) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case FORMATF:
	    if (INTEGER_1 && INTEGER_2 && CHAR_3 && FLOAT_4) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case MAX:
	case MIN:
	    if ((NUMERIC_1 && NUMERIC_2) || (CHAR_1 && CHAR_2)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case MKTIME:
	    if (LIST_1) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case OPCASE:
	    if (LIST_1 && VALID(stk->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case STRFTIME:
	    if (STRING_1 && LIST_2) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case INTERN:
	case STRTOD:
	    if (STRING_1) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case STRTOL:
	    if (INTEGER_1 && STRING_2) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* environment */
	case AUTOPUT:
	case DUMP:
	case ECHO_:
	case MAXINT:
	case MEMORYINDEX:
	case MEMORYMAX_:
	case SETAUTOPUT:
	case SETECHO:
	case SETSIZE:
	case SETTRACEGC:
	case SETUNDEFERROR:
	case SYMTABINDEX:
	case SYMTABMAX_:
	case UNDEFERROR:
	case UNDEFS:

	case HELP:
	case _HELP:
	case HELPDETAIL:
	case MANUAL:
	case HTML_MANUAL:
	case LATEX_MANUAL:
	case MANUAL_LIST:

	case CONTS:
	case FALSE:
	case ID:
	case INCLUDE:
	case TRUE:
	    (*node->u.proc)();
	    continue;

/* this list of builtins refers to runtime objects */
	case ABORT:
	case ARGC:
	case ARGV:
	case CLOCK:
	case FCLOSE:
	case FEOF:
	case FERROR:
	case FFLUSH:
	case FGET:
	case FGETCH:
	case FGETS:
	case FILETIME:
	case FOPEN:
	case FPUT:
	case FPUTCH:
	case FPUTCHARS:
	case FREAD:
	case FREMOVE:
	case FRENAME:
	case FSEEK:
	case FTELL:
	case FWRITE:
	case GET:
	case GETCH:
	case GETENV:
	case PUT:
	case PUTCH:
	case PUTCHARS:
	case QUIT:
	case RAND:
	case SRAND:
	case STDERR:
	case STDIN:
	case STDOUT:
	case SYSTEM:
	case TIME:

/* stack operators */
	case STACK:
	case UNSTACK:
	    DUPLICATE(node);
	    break;

/* arithmetic, binary */
	case MINUS:
	case PLUS:
	    if ((NUMERIC_1 && NUMERIC_2) || (INTEGER_1 && CHAR_2)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case ATAN2:
	case DIVIDE:
	case MUL:
	case POW:
	case REM:
	    if (NUMERIC_1 && NUMERIC_2) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case DIV:
	    if (INTEGER_1 && INTEGER_2) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case LDEXP:
	    if (INTEGER_1 && NUMERIC_2) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* logical, binary */
	case AND:
	case OR:
	case XOR:
	    if (stk->op == stk->next->op && (stk->op == SET_ ||
			(stk->op >= BOOLEAN_ && stk->op <= INTEGER_))) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* comparison, binary */
	case EQL:
	case EQUAL:
	case GEQL:
	case GREATER:
	case LEQL:
	case LESS:
	case NEQL:
	case SAMETYPE:

	case CASTING:

	case SWAP:
	case DUPD:
	case POPD:
	    if (VALID(stk) && VALID(stk->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* aggregate, binary */
	case CONS:
	case HAS:
	    if (AGGREGATE(stk) && VALID(stk->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case SWONS:
	case IN:
	    if (VALID(stk) && AGGREGATE(stk->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case AT:
	case DROP:
	case TAKE:
	    if (INTEGER_1 && AGGREGATE(stk->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case OF:
	    if (AGGREGATE(stk) && INTEGER_2) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case CONCAT:
	    if (AGGREGATE(stk) && AGGREGATE(stk->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case ENCONCAT:
	    if (AGGREGATE(stk) && AGGREGATE(stk->next) &&
				VALID(stk->next->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* comparison, unary */
	case CHAR:
	case _FILE_:
	case FLOAT:
	case INTEGER:
	case LEAF:
	case LIST:
	case LOGICAL:
	case NOT:
	case NULL_:
	case SET:
	case SMALL:
	case STRING:
	case USER:

	case NAME:

	case DUP:
	case POP:
	    if (VALID(stk)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* arithmetic, unary */
	case GMTIME:
	case LOCALTIME:

	case CHR:
	case ORD:
	case PRED:
	case SUCC:
	    if (INTEGER_1) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case ABS:
	case ACOS:
	case ASIN:
	case ATAN:
	case CEIL:
	case COS:
	case COSH:
	case EXP:
	case FLOOR:
	case FREXP:
	case LOG:
	case LOG10:
	case MODF:
	case NEG:
	case ROUND:
	case SIGN:
	case SIN:
	case SINH:
	case SQRT:
	case TAN:
	case TANH:
	case TRUNC:
	    if (NUMERIC_1) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* aggregate, unary */
	case FIRST:
	    if (AGGREGATE(stk)) {
		(*node->u.proc)();
		stk->unmark = 1;
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case REST:
	case SIZE:
	    if (AGGREGATE(stk)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case UNCONS:
	case UNSWONS:
#if 0
	    if (AGGREGATE(stk) && stk->u.lis) {
		(*node->u.proc)();
		stk->next->unmark = stk->unmark = 1;
		continue;
	    } else
#endif
		DUPLICATE(node);
	    break;

	case CHOICE:

	case ROLLDOWN:
	case ROLLUP:
	case ROTATE:
	case SWAPD:
	    if (VALID(stk) && VALID(stk->next) && VALID(stk->next->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

	case ROLLDOWND:
	case ROLLUPD:
	case ROTATED:
	    if (VALID(stk) && VALID(stk->next) && VALID(stk->next->next) &&
					    VALID(stk->next->next->next)) {
		(*node->u.proc)();
		continue;
	    } else
		DUPLICATE(node);
	    break;

/* combinators */
	case STEP:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && arity(prog) <= valid(stk->next)) {
		Node *list;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next) {
		    DUPLICATE(list);
		    stk->unmark = 1;
		    evaluate(prog);
		}
	    } else if (LIST_1 && STRING_2 && arity(prog) <= valid(stk->next)) {
		char *str;

		POP(stk);
		str = stk->u.str;
		POP(stk);
		for (; *str; str++) {
		    PUSH(CHAR_, *str);
		    evaluate(prog);
		}
	    } else if (LIST_1 && SET_2 && arity(prog) <= valid(stk->next)) {
		int i;
		long_t set;

		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			PUSH(INTEGER_, i);
			evaluate(prog);
		    }
	    } else
		DUPLICATE(node);
	    break;
	}

	case BRANCH:
	    if (LIST_1 && LIST_2 && VALID(stk->next->next)) {	// XXX
		int num;
		Node *first, *second;

		second = stk->u.lis;
		POP(stk);
		first = stk->u.lis;
		POP(stk);
		num = stk->u.num;
		POP(stk);
		evaluate(num ? first : second);
	    } else
		DUPLICATE(node);
	    break;

	case IFLIST:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == LIST_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFCHAR:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == CHAR_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFFILE:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == FILE_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFFLOAT:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == FLOAT_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFINTEGER:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == INTEGER_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFLOGICAL:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == BOOLEAN_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFSET:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == SET_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFSTRING:
	{
	    int num;
	    Node *first, *second;

	    second = stk->u.lis;
	    first = stk->next->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(first) < num && arity(second) < num) {
		POP(stk);
		POP(stk);
		evaluate(stk->op == STRING_ ? first : second);
	    } else
		DUPLICATE(node);
	    break;
	}

	case CLEAVE:
	    if (LIST_1 && LIST_2 && VALID(stk->next->next)) {	// XXX
		Node *prog[2], result[2], *save;

		prog[1] = stk->u.lis;
		POP(stk);
		prog[0] = stk->u.lis;
		POP(stk);
		save = stk;
		CONDITION;
		evaluate(prog[0]);
		result[0] = *stk;
		stk = save;
		evaluate(prog[1]);
		result[1] = *stk;
		stk = save;
		RELEASE;
		POP(stk);
		DUPLICATE(&result[0]);
		DUPLICATE(&result[1]);
	    } else
		DUPLICATE(node);
	    break;

	case CONSTRUCT:
	{
	    int i, num;
	    Node *list;

	    num = valid(stk->next);
	    for (list = stk->u.lis; list; list = list->next)
		if ((i = arity(list->u.lis)) > num) {
		    num = 0;
		    break;
		}
	    if (LIST_1 && LIST_2 && num) {
		Node *init, *root = 0, *save[2];

		list = stk->u.lis;
		POP(stk);
		init = stk->u.lis;
		POP(stk);
		save[0] = stk;
		evaluate(init);
		for (; list; list = list->next) {
		    save[1] = stk;
		    CONDITION;
		    evaluate(list->u.lis);
		    root = heapnode(stk->op, stk->u.ptr, root);
		    stk = save[1];
		    RELEASE;
		}
		stk = save[0];
		for (list = root; list; list = list->next)
		DUPLICATE(list);
	    } else
		DUPLICATE(node);
	    break;
	}

	case FOLD:
	    if (LIST_1 && VALID(stk->next) && AGGREGATE(stk->next->next)) {
		Node temp;
		temp.op = stk->next->op;
		temp.u.ptr = stk->next->u.ptr;
		stk->next->op = stk->next->next->op;
		stk->next->u.ptr = stk->next->next->u.ptr;
		stk->next->next->op = temp.op;
		stk->next->next->u.ptr = temp.u.ptr;
		node->op = STEP - FALSE + FALSE_;
		node->u.proc = step_;
		DUPLICATE(node);
	    } else
		DUPLICATE(node);
	    break;

	case I:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) <= valid(stk->next)) {
		POP(stk);
		evaluate(prog);
	    } else
		DUPLICATE(node);
	    break;
	}

	case DIP:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) < valid(stk->next)) {
		Node temp;

		POP(stk);
		temp = *stk;
		POP(stk);
		evaluate(prog);
		DUPLICATE(&temp);
	    } else
		DUPLICATE(node);
	    break;
	}

	case TIMES:
	{
	    int num;
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && INTEGER_2 && arity(prog) <= valid(stk->next->next)) {
		POP(stk);
		num = stk->u.num;
		POP(stk);
		while (num--)
		    evaluate(prog);
	    } else
		DUPLICATE(node);
	    break;
	}

	case MAP:
	{
	    Node *prog, *save;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && arity(prog) <= valid(stk->next)) {
		Node *list, *root = 0, *cur;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next) {
		    save = stk;
		    CONDITION;
		    DUPLICATE(list);
		    evaluate(prog);
		    if (!root)
			cur = root = heapnode(stk->op, stk->u.ptr, 0);
		    else
			cur = cur->next = heapnode(stk->op, stk->u.ptr, 0);
		    stk = save;
		    RELEASE;
		}
		PUSH(LIST_, root);
	    } else if (LIST_1 && STRING_2 && arity(prog) <= valid(stk->next)) {
		int i;
		char *str, *result;

		POP(stk);
		str = stk->u.str;
		POP(stk);
		for (i = 0, result = strdup(str); *str; str++) {
		    save = stk;
		    CONDITION;
		    PUSH(CHAR_, *str);
		    evaluate(prog);
		    result[i++] = stk->u.num;
		    stk = save;
		    RELEASE;
		}
		result[i] = 0;
		PUSH(STRING_, result);
	    } else if (LIST_1 && SET_2 && arity(prog) <= valid(stk->next)) {
		int i;
		long_t set, result;

		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (result = i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			save = stk;
			CONDITION;
			PUSH(INTEGER_, i);
			evaluate(prog);
			result |= 1 << stk->u.num;
			stk = save;
			RELEASE;
		    }
		PUSH(SET_, result);
	    } else
		DUPLICATE(node);
	    break;
	}

	case SOME:
	{
	    Node *prog, *save;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && arity(prog) <= valid(stk->next)) {
		Node *list;
		int num = 0;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next) {
		    save = stk;
		    CONDITION;
		    DUPLICATE(list);
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (num)
			break;
		}
		PUSH(BOOLEAN_, num);
	    } else if (LIST_1 && STRING_2 && arity(prog) <= valid(stk->next)) {
		char *str;
		int num = 0;

		POP(stk);
		str = stk->u.str;
		POP(stk);
		for ( ; str && *str; str++) {
		    save = stk;
		    CONDITION;
		    PUSH(CHAR_, *str);
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (num)
			break;
		}
		PUSH(BOOLEAN_, num);
	    } else if (LIST_1 && SET_2 && arity(prog) <= valid(stk->next)) {
		long_t set;
		int i, num = 0;

		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			save = stk;
			CONDITION;
			PUSH(INTEGER_, i);
			evaluate(prog);
			num = stk->u.num;
			stk = save;
			RELEASE;
			if (num)
			    break;
		    }
		PUSH(BOOLEAN_, num);
	    } else
		DUPLICATE(node);
	    break;
	}

	case ALL:
	{
	    Node *prog, *save;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && arity(prog) <= valid(stk->next)) {
		Node *list;
		int num = 1;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next) {
		    save = stk;
		    CONDITION;
		    DUPLICATE(list);
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (!num)
			break;
		}
		PUSH(BOOLEAN_, num);
	    } else if (LIST_1 && STRING_2 && arity(prog) <= valid(stk->next)) {
		char *str;
		int num = 1;

		POP(stk);
		str = stk->u.str;
		POP(stk);
		for ( ; str && *str; str++) {
		    save = stk;
		    CONDITION;
		    PUSH(CHAR_, *str);
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (!num)
			break;
		}
		PUSH(BOOLEAN_, num);
	    } else if (LIST_1 && SET_2 && arity(prog) <= valid(stk->next)) {
		long_t set;
		int i, num = 1;

		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			save = stk;
			CONDITION;
			PUSH(INTEGER_, i);
			evaluate(prog);
			num = stk->u.num;
			stk = save;
			RELEASE;
			if (!num)
			    break;
		    }
		PUSH(BOOLEAN_, num);
	    } else
		DUPLICATE(node);
	    break;
	}

	case FILTER:
	{
	    Node *prog, *save;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && arity(prog) <= valid(stk->next)) {
		int num = 0;
		Node *list, *root = 0, *cur;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next) {
		    save = stk;
		    CONDITION;
		    DUPLICATE(list);
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (num) {
			if (!root)
			    cur = root = heapnode(list->op, list->u.ptr, 0);
			else
			    cur = cur->next = heapnode(list->op, list->u.ptr,0);
		    }
		}
		PUSH(LIST_, root);
	    } else if (LIST_1 && STRING_2 && arity(prog) <= valid(stk->next)) {
		int i = 0;
		char *str, *result;

		POP(stk);
		str = stk->u.str;
		POP(stk);
		for (result = strdup(str); str && *str; str++) {
		    save = stk;
		    CONDITION;
		    PUSH(CHAR_, *str);
		    evaluate(prog);
		    if (stk->u.num)
			result[i++] = *str;
		    stk = save;
		    RELEASE;
		}
		result[i] = 0;
		PUSH(STRING_, result);
	    } else if (LIST_1 && SET_2 && arity(prog) <= valid(stk->next)) {
		int i;
		long_t set, result = 0;

		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			save = stk;
			CONDITION;
			PUSH(INTEGER_, i);
			evaluate(prog);
			if (stk->u.num)
			    result |= 1 << i;
			stk = save;
			RELEASE;
		    }
		PUSH(SET_, result);
	    } else
		DUPLICATE(node);
	    break;
	}

	case SPLIT:
	{
	    Node *prog, *save;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && arity(prog) <= valid(stk->next)) {
		int num = 0;
		Node *list, *root = 0, *cur, *head = 0, *tail;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next) {
		    save = stk;
		    CONDITION;
		    DUPLICATE(list);
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (num)
			if (!root)
			    cur = root = heapnode(list->op, list->u.ptr, 0);
			else
			    cur = cur->next = heapnode(list->op, list->u.ptr,0);
		    else if (!head)
			tail = head = heapnode(list->op, list->u.ptr, 0);
		    else
			tail = tail->next = heapnode(list->op, list->u.ptr, 0);
		}
		PUSH(LIST_, root);
		PUSH(LIST_, head);
	    } else if (LIST_1 && STRING_2 && arity(prog) <= valid(stk->next)) {
		int i = 0, j = 0;
		char *str, *result[2];

		POP(stk);
		str = stk->u.str;
		POP(stk);
		result[0] = strdup(str);
		result[1] = strdup(str);
		for (; str && *str; str++) {
		    save = stk;
		    CONDITION;
		    PUSH(CHAR_, *str);
		    evaluate(prog);
		    if (stk->u.num)
			result[0][i++] = *str;
		    else
			result[1][i++] = *str;
		    stk = save;
		    RELEASE;
		}
		result[0][i] = 0;
		result[1][j] = 0;
		PUSH(STRING_, result[0]);
		PUSH(STRING_, result[1]);
	    } else if (LIST_1 && SET_2 && arity(prog) <= valid(stk->next)) {
		int i;
		long_t set, result[2];

		result[0] = result[1] = 0;
		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			save = stk;
			CONDITION;
			PUSH(INTEGER_, i);
			evaluate(prog);
			if (stk->u.num)
			    result[0] |= 1 << i;
			else
			    result[1] |= 1 << i;
			stk = save;
			RELEASE;
		    }
		PUSH(SET_, result[0]);
		PUSH(SET_, result[1]);
	    } else
		DUPLICATE(node);
	    break;
	}

	case NULLARY:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) <= valid(stk->next)) {
		Node *top, *result;

		POP(stk);
		top = stk;
		CONDITION;
		evaluate(prog);
		RELEASE;
		result = stk;
		stk = top;
		DUPLICATE(result);
	    } else
		DUPLICATE(node);
	    break;
	}

	case UNARY:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) <= valid(stk->next)) {
		Node *top, *result;

		POP(stk);
		top = stk->next;
		CONDITION;
		evaluate(prog);
		RELEASE;
		result = stk;
		stk = top;
		DUPLICATE(result);
	    } else
		DUPLICATE(node);
	    break;
	}

	case BINARY:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) <= valid(stk->next)) {
		Node *top, *result;

		POP(stk);
		top = stk->next->next;
		CONDITION;
		evaluate(prog);
		RELEASE;
		result = stk;
		stk = top;
		DUPLICATE(result);
	    } else
		DUPLICATE(node);
	    break;
	}

	case TERNARY:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) <= valid(stk->next)) {
		Node *top, *result;

		POP(stk);
		top = stk->next->next->next;
		CONDITION;
		evaluate(prog);
		RELEASE;
		result = stk;
		stk = top;
		DUPLICATE(result);
	    } else
		DUPLICATE(node);
	    break;
	}

	case UNARY2:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && VALID(stk->next) &&
			  arity(prog) < valid(stk->next->next)) {
		Node temp, *top, result[2];

		POP(stk);
		temp = *stk;
		POP(stk);
		top = stk->next;
		CONDITION;
		evaluate(prog);
		result[0] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&temp);
		CONDITION;
		evaluate(prog);
		result[1] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&result[0]);
		DUPLICATE(&result[1]);
	    } else
		DUPLICATE(node);
	    break;
	}

	case UNARY3:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && VALID(stk->next) && VALID(stk->next->next) &&
			  arity(prog) < valid(stk->next->next->next)) {
		Node first, second, *top, result[3];

		POP(stk);
		second = *stk;
		POP(stk);
		first = *stk;
		POP(stk);
		top = stk->next;
		CONDITION;
		evaluate(prog);
		result[0] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&first);
		CONDITION;
		evaluate(prog);
		result[1] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&second);
		CONDITION;
		evaluate(prog);
		result[2] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&result[0]);
		DUPLICATE(&result[1]);
		DUPLICATE(&result[2]);
	    } else
		DUPLICATE(node);
	    break;
	}

	case UNARY4:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && VALID(stk->next) && VALID(stk->next->next) &&
			  VALID(stk->next->next->next) &&
			  arity(prog) < valid(stk->next->next->next->next)) {
		Node first, second, third, *top, result[4];

		POP(stk);
		third = *stk;
		POP(stk);
		second = *stk;
		POP(stk);
		first = *stk;
		POP(stk);
		top = stk->next;
		CONDITION;
		evaluate(prog);
		result[0] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&first);
		CONDITION;
		evaluate(prog);
		result[1] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&second);
		CONDITION;
		evaluate(prog);
		result[2] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&third);
		CONDITION;
		evaluate(prog);
		result[3] = *stk;
		RELEASE;
		stk = top;
		DUPLICATE(&result[0]);
		DUPLICATE(&result[1]);
		DUPLICATE(&result[2]);
		DUPLICATE(&result[3]);
	    } else
		DUPLICATE(node);
	    break;
	}

	case X:
	{
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && arity(prog) <= valid(stk))
		evaluate(prog);
	    else
		DUPLICATE(node);
	    break;
	}

	case WHILE:
	{
	    int num;
	    Node *prog;

	    prog = stk->u.lis;
	    num = valid(stk->next->next);
	    if (LIST_1 && LIST_2 && arity(prog) <= num &&
			arity(stk->next->u.lis) <= num) {
		int num;
		Node *list, *save;

		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (;;) {
		    save = stk;
		    CONDITION;
		    evaluate(list);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (!num)
			break;
		    evaluate(prog);
		}
	    } else
		DUPLICATE(node);
	    break;
	}

	case IFTE:
	{
	    int num;

	    num = valid(stk->next->next->next);
	    if (LIST_1 && LIST_2 && LIST_3 && arity(stk->u.lis) <= num &&
					arity(stk->next->u.lis) <= num &&
				  arity(stk->next->next->u.lis) <= num) {
		Node *second, *first, *list, *save;
		second = stk->u.lis;
		POP(stk);
		first = stk->u.lis;
		POP(stk);
		list = stk->u.lis;
		POP(stk);
		save = stk;
		CONDITION;
		evaluate(list);
		list = stk->u.num ? first : second;
		stk = save;
		RELEASE;
		evaluate(list);
	    } else
		DUPLICATE(node);
	    break;
	}

	case INFRA:
	    if (LIST_1 && LIST_2 && VALID(stk->next->next)) {	// XXX
		Node *prog, *list, *save;

		prog = stk->u.lis;
		POP(stk);
		list = stk->u.lis;
		POP(stk);
		save = stk2lst();
		lst2stk(list);
		evaluate(prog);
		list = stk2lst();
		lst2stk(save);
		PUSH(LIST_, list);
	    } else
		DUPLICATE(node);
	    break;

	case COND:
	{
	    int i, num;
	    Node *list;

	    num = valid(stk->next);
	    for (list = stk->u.lis; list && list->next; list = list->next)
		if ((i = arity(stk->u.lis->u.lis)) > num) {
		    num = 0;
		    break;
		}
	    if (LIST_1 && num) {
		Node *prog, *save;

		list = stk->u.lis;
		POP(stk);
		for ( ; list->next; list = list->next) {
		    prog = list->u.lis->u.lis;
		    save = stk;
		    CONDITION;
		    evaluate(prog);
		    num = stk->u.num;
		    stk = save;
		    RELEASE;
		    if (num)
			break;
		}
		evaluate(num ? list->u.lis->next : list->u.lis);
	    } else
		DUPLICATE(node);
	    break;
	}

	case BINREC:
	case CONDLINREC:
	case CONDNESTREC:
	case GENREC:
	case LINREC:
	case TAILREC:
	case TREEGENREC:
	case TREEREC:
	case TREESTEP:
	    DUPLICATE(node);
	    break;

	case CASE:
	{
	    int error;
	    Node *prog;

	    prog = stk->u.lis;
	    if (LIST_1 && prog && arity(prog) < valid(stk->next)) {
		POP(stk);
		for ( ; prog->next; prog = prog->next)
		    if (!Compare(prog->u.lis, stk, &error) && !error)
			break;
		if (prog->next) {
		    POP(stk);
		    evaluate(prog->u.lis->next);
		} else
		    evaluate(prog->u.lis);
	    } else
		DUPLICATE(node);
	    break;
	}

	case PRIMREC:
	{
	    int i, num = 0;
	    Node *prog, *init;

	    prog = stk->u.lis;
	    if (LIST_1 && LIST_2 && LIST_3 && arity(prog) <= valid(stk->next)) {
		Node *list;

		POP(stk);
		init = stk->u.lis;
		POP(stk);
		list = stk->u.lis;
		POP(stk);
		for (; list; list = list->next, num++)
		    DUPLICATE(list);
		evaluate(init);
		for (i = 0; i < num; i++)
		    evaluate(prog);
	    } else if (LIST_1 && LIST_2 && STRING_3 &&
			arity(prog) <= valid(stk->next)) {
		char *str;

		POP(stk);
		init = stk->u.lis;
		POP(stk);
		str = stk->u.str;
		POP(stk);
		for (; str && *str; str++, num++)
		    PUSH(CHAR_, *str);
		evaluate(init);
		for (i = 0; i < num; i++)
		    evaluate(prog);
	    } else if (LIST_1 && LIST_2 && SET_3 &&
			arity(prog) <= valid(stk->next)) {
		long_t set;

		POP(stk);
		init = stk->u.lis;
		POP(stk);
		set = stk->u.set;
		POP(stk);
		for (i = 0; i < _SETSIZE_; i++)
		    if (set & (1 << i)) {
			PUSH(INTEGER_, i);
			num++;
		    }
		evaluate(init);
		for (i = 0; i < num; i++)
		    evaluate(prog);
	    } else if (LIST_1 && LIST_2 && INTEGER_3 &&
			arity(prog) <= valid(stk->next)) {
		int num;

		POP(stk);
		init = stk->u.lis;
		POP(stk);
		num = stk->u.num;
		POP(stk);
		for (i = num; i > 0; i--)
		    PUSH(INTEGER_, i);
		evaluate(init);
		for (i = 0; i < num; i++)
		    evaluate(prog);
	    } else
		DUPLICATE(node);
	    break;
	}

	case t_USR:
	    if (!node->u.ent->uniq) {
		fprintf(stderr, "undefined %s\n", node->u.ent->name);
		continue;
	    } else
		DUPLICATE(node);
	    break;

	default:
	    fprintf(stderr, "unknown %d\n", node->op);
	    continue;
	}

/* mark code that is stored on the stack */
	stk->mark = 1;
    }
}

void optimize(Node *cur, UT_string *library);

void dump()
{
    Entry *sym;

    for (sym = symtab; sym < symtabindex; sym++) {
	fprintf(stderr, "%s == ", sym->name);
	writeterm(sym->u.body, stderr);
	fprintf(stderr, "\n");
    }
}

void EvalPrintTerm(Node *prog, UT_string *str)
{
    Node *cur;

    stk = &memory[MEMORYMAX];
    evaluate(prog);
    prog = reverse(stk2prog());
    for (cur = prog; cur; cur = cur->next)
	optimize(cur, library);
    PrintTerm(reverse(prog), str);
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
		utstring_new(str);
		sym->mark = changed = 1;
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
#ifdef TRACE
    trace = 0;
#endif
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

void compile(Node *cur)
{
    Entry *sym;

    if (!declhdr) {
	atexit(exitcompile);
	utstring_new(declhdr);
	utstring_new(program);
	utstring_new(library);
    }
    if (cur)
	EvalPrintTerm(cur, program);
    utstring_printf(program, "writestack();\n");
    for (sym = symtab; sym < symtabindex; sym++)
	sym->is_used = 0;
}
