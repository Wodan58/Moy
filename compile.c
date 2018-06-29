/*
    module  : compile.c
    version : 1.29
    date    : 06/29/18
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
    ptr = GC_malloc_atomic(leng + 1);
    StringPrint(ptr, str);
    return ptr;
}

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

static void PrintMember(Node *cur, int list, unsigned *pindex, FILE *fp)
{
    char *name;
    int offset;
    unsigned flags, index = *pindex;

    if (!cur)
	return;
    fprintf(fp, "{");
    switch (cur->op) {
    case BOOLEAN_:
	fprintf(fp, ".u.num=%d,", cur->u.num != 0);
	fprintf(fp, ".op=BOOLEAN_");
	break;
    case CHAR_:
	fprintf(fp, ".u.num=%d,", (int)cur->u.num);
	fprintf(fp, ".op=CHAR_");
	break;
    case INTEGER_:
	fprintf(fp, ".u.num=%lld,", (long long)cur->u.num);
	fprintf(fp, ".op=INTEGER_");
	break;
    case SET_:
	fprintf(fp, ".u.num=%llu,", (unsigned long long)cur->u.num);
	fprintf(fp, ".op=SET_");
	break;
    case STRING_:
	fprintf(fp, ".u.str=%s,", PrintString(cur->u.str));
	fprintf(fp, ".op=STRING_");
	break;
    case LIST_:
	if (cur->u.lis)
	    fprintf(fp, ".u.lis=L%d+%d,", list, index + 1);
	fprintf(fp, ".op=LIST_");
	if (cur->next)
	    fprintf(fp, ",.next=L%d+%d", list,
			index + 1 + ListLeng(cur->u.lis));
	fprintf(fp, "},\n");
	*pindex = index + 1;
	for (cur = cur->u.lis; cur; cur = cur->next)
	    PrintMember(cur, list, pindex, fp);
	return;
    case FLOAT_:
	fprintf(fp, ".u.dbl=%g,", cur->u.dbl);
	fprintf(fp, ".op=FLOAT_");
	break;
    case USR_:
	offset = cur->u.num;
	flags = dict_flags(offset);
	dict_setflags(offset, flags | IS_USED);
	if (dict_body(offset)) {
	    name = dict_nickname(offset);
	    fprintf(fp, ".u.proc=do_%s,", name);
	    fprintf(fp, ".op=ANON_FUNCT_");
	} else {
	    name = dict_name(offset);
	    fprintf(fp, ".u.str=\"%s\",", name);
	    fprintf(fp, ".op=SYMBOL_");
	}
	break;
    default:
	name = printname(cur->op);
	offset = lookup(name);
	flags = dict_flags(offset);
	dict_setflags(offset, flags | IS_USED);
	name = opername(cur->op);
	fprintf(fp, ".u.proc=do_%s,", name);
	fprintf(fp, ".op=ANON_FUNCT_");
	break;
    }
    if (cur->next)
	fprintf(fp, ",.next=L%d+%d", list, index + 1);
    fprintf(fp, "},\n");
    *pindex = index + 1;
}

static unsigned PrintList(Node *cur, FILE *fp, int head)
{
    int found;
    unsigned list, leng, index = 0;

    if (!cur)
	return 0;
    list = Listed(cur, &found);
    if (!found) {
	leng = ListLeng(cur);
	fprintf(fp, "static Node L%d[%d] = {\n", list, leng);
	for (; cur; cur = cur->next) {
	    PrintMember(cur, list, &index, fp);
	    if (head)
		break;
	}
	fprintf(fp, "};");
    }
    return list;
}

static void PrintDecl(Node *root)
{
    int index;
    Node *cur;
    char *name;
    unsigned flags;

    for (cur = root; cur; cur = cur->next) {
	switch (cur->op) {
	case LIST_:
	    PrintDecl(cur->u.lis);
	    break;

	case USR_:
	    index = cur->u.num;
	    flags = dict_flags(index);
	    if (dict_body(index) && (flags & IS_DECLARED) == 0) {
		flags |= IS_DECLARED | IS_USED;
		name = dict_nickname(index);
		fprintf(declfp, "void do_%s(void);", name);
	    }
	    dict_setflags(index, flags | IS_USED);
	    break;
	}
    }
}

static unsigned printnode(Node *node, FILE *fp)
{
    unsigned list = 0;

    switch (node->op) {
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
	fprintf(fp, "PUSH(STRING_,%s);", PrintString(node->u.str));
	break;
    case LIST_:
	PrintDecl(node->u.lis);
	if ((list = PrintList(node->u.lis, fp, 0)) == 0)
	    fprintf(fp, "PUSH(LIST_,0);");
	else
	    fprintf(fp, "PUSH(LIST_, L%d);", list);
	break;
    case FLOAT_:
	fprintf(fp, "DBL_PUSH((real_t)%g);", node->u.dbl);
	break;
    case USR_:
    case SYMBOL_:
	fprintf(fp, "PUSH(SYMBOL_,\"");
	writefactor(node, fp);
	fprintf(fp, "\");");
	break;
    default:
	execerror("valid datatype", "printnode");
	break;
    }
    return list;
}

static void printrecur(Node *node, FILE *fp)
{
    if (!node || node == memory)
	return;
    printrecur(node->next, fp);
    printnode(node, fp);
}

unsigned PrintHead(Node *node, FILE *fp)
{
    PrintDecl(node->u.lis);
    return PrintList(node->u.lis, fp, 1);
}

void printstack(FILE *fp)
{
    printrecur(stk, fp);
    stk = memory;
}

void initialise(void)
{
    time_t t = time(0);

    if (!mainfunc)
	mainfunc = "main";
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#define NCHECK\n");
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
    int i, j, leng, index, changed;

    if (end_of_main)
	fprintf(outfp, "}");
    else {
	end_of_main = 1;
	fprintf(outfp, "return 0; /* main */ }");
    }
    if (optimizing)
	clr_history();
    do {
	leng = dict_size();
	for (changed = i = 0; i < leng; i++) {
	    flags = dict_flags(i);
	    body = dict_body(i);
	    if (!(flags & IS_BUILTIN) && body && (flags & IS_USED) &&
		!(flags & IS_PRINTED)) {
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
		DeList();
		evaluate(body);
		fprintf(outfp, "}");
	    }
	}
    } while (changed);
    fprintf(outfp, "\n");
    printout();
    closeout();

    printf("struct {\nproc_t proc;\n");
    printf("char *name;\n} table[] = {\n");
    iterate_dict_and_write_struct();
    printf("{ 0, 0 },\n};\n\n");
    printf("char *procname(proc_t proc)\n{\n");
    printf("int i;\n\nfor (i = 0; table[i].proc; i++)\n");
    printf("if (proc == table[i].proc)\n");
    printf("return table[i].name;\n");
    printf("return 0;\n}\n\n");
    printf("proc_t nameproc(char *name)\n{\n");
    printf("int i;\n\nfor (i = 0; table[i].proc; i++)\n");
    printf("if (!strcmp(name, table[i].name))\n");
    printf("return table[i].proc;\n");
    printf("return 0;\n}\n\n");
}
