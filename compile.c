/*
    module  : compile.c
    version : 1.43
    date    : 11/23/20
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

static unsigned ListLeng(Node *cur)
{
    unsigned leng;

    for (leng = 0; cur; cur = cur->next) {
	leng++;
	if (cur->op == LIST_)
	    leng += ListLeng(cur->u.lis);
    }
    return leng;
}

static unsigned StringLeng(char *str)
{
    unsigned i;

    for (i = 2; *str; i++, str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13))
	    i++;
	else if (iscntrl((int) *str))
	    i += 3;
    return i;
}

static void StringPrint(char *ptr, char *str)
{
    for (*ptr++ = '"'; *str; str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13)) {
	    *ptr++ = '\\';
	    switch (*str) {
	    case '"':
	    case '\'':
	    case '\\':
		*ptr++ = *str;
		break;
	    case 8:
		*ptr++ = 'b';
		break;
	    case 9:
		*ptr++ = 't';
		break;
	    case 10:
		*ptr++ = 'n';
		break;
	    case 11:
		*ptr++ = 'v';
		break;
	    case 12:
		*ptr++ = 'f';
		break;
	    case 13:
		*ptr++ = 'r';
		break;
	    }
	} else if (iscntrl((int) *str)) {
	    sprintf(ptr, "\\%03o", *str);
	    ptr += 4;
	} else
	    *ptr++ = *str;
    *ptr++ = '"';
    *ptr = 0;
}

static char *PrintString(char *str)
{
    char *ptr;
    unsigned leng;

    leng = StringLeng(str);
    ptr = ck_malloc_sec(leng + 1);
    StringPrint(ptr, str);
    return ptr;
}

static Node *copy(Node *node)
{
    Node *my_root = 0, **cur;

    for (cur = &my_root; node; node = node->next) {
	if ((*cur = ck_malloc(sizeof(Node))) == 0)
	    return 0;
	**cur = *node;
	cur = &(*cur)->next;
	*cur = 0;
    }
    return my_root;
}

static void printlist(Node *cur, FILE *fp);

static void printmember(Node *cur, FILE *fp)
{
    int index;
    char *name;
    unsigned flags;

    switch (cur->op) {
    case USR_ :
	index = cur->u.num;
	if (dict_body(index) == 0) {
	    name = dict_name(index);
	    fprintf(fp, "list = SYM_NEWNODE(\"%s\", list);", name);
	} else {
	    flags = dict_flags(index);
	    name = dict_nickname(index);
	    if ((flags & IS_BUILTIN) == 0) {
		if ((flags & IS_DECLARED) == 0) {
		    flags |= IS_DECLARED;
		    fprintf(declfp, "void do_%s(void);", name);
		}
	    }
	    dict_setflags(index, flags |= IS_USED);
	    fprintf(fp, "list = ANON_FUNCT_NEWNODE(do_%s, list);", name);
	}
	break;
    case ANON_FUNCT_ :
	name = procname(cur->u.proc);
	fprintf(fp, "list = ANON_FUNCT_NEWNODE(do_%s, list);", name);
	break;
    case BOOLEAN_ :
	fprintf(fp, "list = BOOLEAN_NEWNODE(%d, list);", cur->u.num != 0);
	break;
    case CHAR_ :
	fprintf(fp, "list = CHAR_NEWNODE(%d, list);", (int)cur->u.num);
	break;
    case INTEGER_ :
	fprintf(fp, "list = INTEGER_NEWNODE(" PRINT_NUM ", list);", cur->u.num);
	break;
    case SET_ :
	fprintf(fp, "list = SET_NEWNODE(" PRINT_SET ", list);", cur->u.set);
	break;
    case STRING_ :
	if (!cur->u.str)
	    fprintf(fp, "list = STRING_NEWNODE(0, list);");
	else {
	    name = PrintString(cur->u.str);
	    fprintf(fp, "list = STRING_NEWNODE(%s, list);", name);
	}
	break;
    case LIST_ :
	if (!cur->u.lis)
	    fprintf(fp, "list = LIST_NEWNODE(0, list);");
	else {
	    printlist(cur->u.lis,fp);
	    fprintf(fp, "list = LIST_NEWNODE(stk->u.lis, list);");
	    fprintf(fp, "POP(stk);");
	}
	break;
    case FLOAT_ :
	fprintf(fp, "list = FLOAT_NEWNODE(%g, list);", cur->u.dbl);
	break;
    default :
	execerror("valid datatype", "printmember");
	break;
    }
}

typedef struct NodeList {
    int seqnr, print;
    Node *node;
    struct NodeList *next;
} NodeList;

static NodeList *root;

int identical_list(Node *first, Node *second);

static int FindNode(Node *node)
{
    static int seqnr;
    NodeList *cur;

    for (cur = root; cur; cur = cur->next)
	if (identical_list(node, cur->node))
	    return cur->seqnr;
    cur = ck_malloc(sizeof(NodeList));
    cur->print = 0;
    cur->seqnr = ++seqnr;
    cur->node = copy(node);
    cur->next = root;
    root = cur;
    fprintf(declfp, "void push_list_%d(void);", seqnr);
    return seqnr;
}

static int PrintNode(FILE *fp)
{
    Node *node;
    int changed;
    NodeList *cur;

    for (changed = 0, cur = root; cur; cur = cur->next) {
	if (cur->print)
	    continue;
	changed = cur->print = 1;
	fprintf(fp, "void push_list_%d(void) {", cur->seqnr);
	fprintf(fp, "static Node *list;");
	fprintf(fp, "if (!list) {");
	for (node = reverse(copy(cur->node)); node; node = node->next)
	    printmember(node, fp);
	fprintf(fp, "} PUSH(LIST_, list); }");
    }
    return changed;
}

static void printlist(Node *cur, FILE *fp)
{
    fprintf(fp, "push_list_%d();", FindNode(cur));
}

void printnode(Node *node, FILE *fp)
{
    Node *cur;
    int index;
    char *name;
    unsigned flags;

    switch (node->op) {
    case USR_ :
	index = node->u.num;
	if ((cur = dict_body(index)) == 0) {
	    name = dict_name(index);
	    fprintf(fp, "PUSH(SYMBOL_, \"%s\");", name);
	} else {
	    flags = dict_flags(index);
	    name = dict_nickname(index);
	    if ((flags & IS_BUILTIN) == 0) {
		if ((flags & IS_ACTIVE) == 0 && (flags & IS_USED) == 0) {
		    dict_setflags(index, flags | IS_ACTIVE);
		    compile(cur);
		    flags = dict_flags(index);
		    dict_setflags(index, flags & ~IS_ACTIVE);
		    break;
		}
		if ((flags & IS_DECLARED) == 0) {
		    flags |= IS_DECLARED;
		    fprintf(declfp, "void do_%s(void);", name);
		}
	    }
	    dict_setflags(index, flags | IS_USED);
	    fprintf(outfp, "do_%s();", name);
	}
	break;
    case BOOLEAN_:
	fprintf(fp, "PUSH(BOOLEAN_, %d);", node->u.num != 0);
	break;
    case CHAR_:
	fprintf(fp, "PUSH(CHAR_, %d);", (int)node->u.num);
	break;
    case INTEGER_:
	fprintf(fp, "PUSH(INTEGER_, " PRINT_NUM ");", node->u.num);
	break;
    case SET_:
	fprintf(fp, "PUSH(SET_, " PRINT_SET ");", node->u.set);
	break;
    case STRING_:
	name = PrintString(node->u.str);
	fprintf(fp, "PUSH(STRING_, %s);", name);
	break;
    case LIST_:
	if (!node->u.lis)
	    fprintf(fp, "PUSH(LIST_, 0);");
	else
	    printlist(node->u.lis, fp);
	break;
    case FLOAT_:
	fprintf(fp, "DBL_PUSH((real_t)%g);", node->u.dbl);
	break;
    case SYMBOL_:
	fprintf(fp, "PUSH(SYMBOL_, \"%s\");", node->u.str);
	break;
    default:
	execerror("valid datatype", "printnode");
	break;
    }
}

void printstack(FILE *fp)
{
    for (stk = reverse(stk); stk; stk = stk->next)
	printnode(stk, fp);
}

void compile(Node *node)
{
    for (printstack(outfp); node; node = node->next)
	printnode(node, outfp);
}

void initialise(void)
{
    time_t t = time(0);

    atexit(finalise);
    fprintf(declfp = stdout, "/*\n * generated %s */\n", ctime(&t));
    fprintf(declfp, "#define OLD_RUNTIME\n");
    fprintf(declfp, "#include \"runtime.h\"\n");
    initout();
    if ((outfp = nextfile()) == 0) {
	fprintf(stderr, "Failed to open outfile\n");
	exit(1);
    }
    fprintf(outfp, "int yyparse() {");
}

static void declare(FILE *fp)
{
    char *name;
    unsigned flags;
    int i, j, leng;

    leng = dict_size();
    for (i = 0; i < leng; i++) {
	flags = dict_flags(i);
	if (((flags & IS_ORIGINAL) && !(flags & IS_BUILTIN)) ||
	    ((flags & IS_ORIGINAL) && !(flags & IS_USED))) {
	    fprintf(fp, "#define ");
	    name = dict_nickname(i);
	    for (j = 0; name[j]; j++)
		fputc(toupper(name[j]), fp);
	    fprintf(fp, "_X\n");
	    fprintf(fp, "#define ");
	    for (j = 0; name[j]; j++)
		fputc(toupper(name[j]), fp);
	    fprintf(fp, "_C\n");
	}
    }
}

void finalise(void)
{
    Node *body;
    unsigned flags;
    char *name, *parm;
    int i, j, leng, changed;

    fprintf(outfp, "return 0; }");
    do {
	changed = PrintNode(outfp);
	for (leng = dict_size(), i = 0; i < leng; i++) {
	    if ((flags = dict_flags(i)) & IS_BUILTIN)
		continue;
	    if ((body = dict_body(i)) == 0)
		continue;
	    if ((flags & IS_USED) && (flags & IS_PRINTED) == 0) {
		dict_setflags(i, flags | IS_PRINTED);
		name = dict_nickname(i);
		if (body->op == USR_) {
		    j = body->u.num;
		    parm = dict_nickname(j);
		    if (!strcmp(name, parm))
			continue;
		}
		changed = 1;
		fprintf(outfp, "void do_%s(void) {", name);
		compile(body);
		fprintf(outfp, "}");
	    }
	}
    } while (changed);
    printout(declfp);
    closeout();
    fprintf(declfp, "table_t table[] = {");
    iterate_dict_and_write_struct(declfp);
    fprintf(declfp, "{ 0, 0 }, };");
    declare(declfp);
    fprintf(declfp, "#include \"interp.c\"\n");
}
