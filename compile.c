/*
    module  : compile.c
    version : 1.25
    date    : 05/26/17
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"

char *usrname(char *str)
{
    char *ptr;
    unsigned i;

    if (strchr(ptr = str, '-')) {
	ptr = GC_strdup(str);
	for (i = 0; ptr[i]; i++)
	    if (ptr[i] == '-')
		ptr[i] = '_';
    }
    return ptr;
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
    Entry *sym;
    char *name;
    unsigned index = *pindex;

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
	sym = cur->u.ent;
	name = usrname(sym->name);
	if (sym->u.body) {
	    fprintf(fp, ".u.proc=do_%s,", name);
	    fprintf(fp, ".op=ANON_FUNCT_");
	} else {
	    fprintf(fp, ".u.str=\"%s\",", name);
	    fprintf(fp, ".op=SYMBOL_");
	}
	break;
    default:
	fprintf(fp, ".u.proc=do_%s,", opername(cur->op));
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
    Node *cur;
    Entry *sym;
    char *name;

    for (cur = root; cur; cur = cur->next)
	switch (cur->op) {
	case LIST_:
	    PrintDecl(cur->u.lis);
	    break;

	case USR_:
	    sym = cur->u.ent;
	    if (sym->u.body) {
		sym->flags |= IS_USED;
		name = usrname(sym->name);
		fprintf(declfp, "void do_%s(void);", name);
	    }
	    break;
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
	fprintf(stderr, "unknown; %d\n", node->op);
	break;
    }
    return list;
}

static void printrecur(Node *node, FILE *fp)
{
    if (node == memory)
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
    printf("#include \"runtime.c\"\n");
    initout();
    outfp = nextfile();
    fprintf(outfp, "int %s(int argc, char **argv) {", mainfunc);
    fprintf(outfp, "initsym(argc, argv);");
    declfp = stdout;
}

void finalise(void)
{
    Entry *sym;
    Node *code;
    char *name, *parm;
    unsigned i, changed;

    if (optimizing)
	clr_history();
    fprintf(outfp, "return 0; }");
    do
	for (changed = i = 0; i < symtabindex; i++)
	    if ((symtab[i].flags & (IS_PRINTED | IS_USED)) == IS_USED) {
		symtab[i].flags |= IS_PRINTED;
		name = usrname(symtab[i].name);
		code = symtab[i].u.body;
		if (code->op == USR_) {
		    sym = code->u.ent;
		    parm = usrname(sym->name);
		    if (!strcmp(name, parm))
			continue;
		}
		changed = 1;
		fprintf(outfp, "void do_%s(void) {", name);
		DeList();
		evaluate(symtab[i].u.body);
		fprintf(outfp, "}");
	    }
    while (changed);
    fprintf(outfp, "\n");
    printout();
    closeout();
}
