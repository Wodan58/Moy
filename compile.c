/*
    module  : compile.c
    version : 1.30
    date    : 07/02/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"

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
    Node *root = 0, **cur;

    for (cur = &root; node; node = node->next) {
	if ((*cur = malloc(sizeof(Node))) == 0)
	    return 0;
	**cur = *node;
	cur = &(*cur)->next;
	*cur = 0;
    }
    return root;
}

static void printlist(Node *node, FILE *fp)
{
    Node *cur;
    int index;
    char *name;
    unsigned flags;

    node = reverse(copy(node));
    for (cur = node; cur; cur = cur->next) {
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
	    fprintf(fp, "list = CHAR_NEWNODE(%d, list);", cur->u.num);
	    break;
	case INTEGER_ :
	    fprintf(fp, "list = INTEGER_NEWNODE(%d, list);", cur->u.num);
	    break;
	case SET_ :
	    fprintf(fp, "list = SET_NEWNODE(%d, list);", cur->u.num);
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
		fprintf(fp, "{ Node *list = 0;");
		printlist(cur->u.lis, fp);
		fprintf(fp, "PUSH(LIST_, list); }");
		fprintf(fp, "list = LIST_NEWNODE(stk->u.lis, list);");
		fprintf(fp, "POP(stk);");
	    }
	    break;
	case FLOAT_ :
	    fprintf(fp, "list = FLOAT_NEWNODE(%f, list);", cur->u.dbl);
	    break;
	default :
	    execerror("valid datatype", "printlist");
	    break;
	}
    }
}

static void printnode(Node *node, FILE *fp)
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
	fprintf(fp, "PUSH(INTEGER_, %lld);", (long long)node->u.num);
	break;
    case SET_:
	fprintf(fp, "PUSH(SET_, %llu);", (unsigned long long)node->u.set);
	break;
    case STRING_:
	fprintf(fp, "PUSH(STRING_, %s);", PrintString(node->u.str));
	break;
    case LIST_:
	if (!node->u.lis)
	    fprintf(fp, "PUSH(LIST_, 0);");
	else {
	    fprintf(fp, "{ Node *list = 0;");
	    printlist(node->u.lis, fp);
	    fprintf(fp, "PUSH(LIST_, list); }");
	}
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

void PrintHead(Node *node, FILE *fp)
{
    printnode(node, fp);
}

static void printrecur(Node *node, FILE *fp)
{
    if (node) {
	printrecur(node->next, fp);
	printnode(node, fp);
    }
}

void printstack(FILE *fp)
{
    printrecur(stk, fp);
    stk = 0;
}

void compile(Node *node)
{
    printstack(outfp);
    for (; node; node = node->next)
	printnode(node, outfp);
}

void initialise(void)
{
    time_t t = time(0);

    if (!mainfunc)
	mainfunc = "main";
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#include \"runtime.h\"\n");
    initout();
    outfp = nextfile();
    fprintf(outfp, "int %s(int argc, char **argv) {", mainfunc);
    fprintf(outfp, "initsym(argc, argv);");
    declfp = stdout;
}

void finalise(void)
{
    static int end_of_main;
    Node *body;
    unsigned flags;
    char *name, *parm;
    int i, j, leng, changed;

    if (end_of_main)
	fprintf(outfp, "}");
    else {
	end_of_main = 1;
	fprintf(outfp, "return 0; }");
    }
    do {
	leng = dict_size();
	for (changed = i = 0; i < leng; i++) {
	    flags = dict_flags(i);
	    body = dict_body(i);
	    if ((flags & IS_BUILTIN) == 0 && body && (flags & IS_USED) &&
		(flags & IS_PRINTED) == 0) {
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
    printout();
    closeout();

    printf("struct { proc_t proc; ");
    printf("char *name; } table[] = {");
    iterate_dict_and_write_struct();
    printf("{ 0, 0 }, };");
    printf("char *procname(proc_t proc) {");
    printf("int i; for (i = 0; table[i].proc; i++)");
    printf("if (proc == table[i].proc)");
    printf("return table[i].name;");
    printf("return 0; }");
    printf("proc_t nameproc(char *name) {");
    printf("int i; for (i = 0; table[i].proc; i++)");
    printf("if (!strcmp(name, table[i].name))");
    printf("return table[i].proc;");
    printf("return 0; }\n");
}
