/*
    module  : compile.c
    version : 1.46
    date    : 03/16/21
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

static int ListLeng(Node *cur)
{
    int leng;

    for (leng = 0; cur; cur = cur->next) {
	leng++;
	if (cur->op == LIST_)
	    leng += ListLeng(cur->u.lis);
    }
    return leng;
}

static int StringLeng(char *str)
{
    int i;

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
    int leng;
    char *ptr;

    leng = StringLeng(str);
    ptr = GC_malloc_atomic(leng + 1);
    StringPrint(ptr, str);
    return ptr;
}

static Node *copy(Node *node)
{
    Node *my_root = 0, **cur;

    for (cur = &my_root; node; node = node->next) {
	if ((*cur = GC_malloc(sizeof(Node))) == 0)
	    return 0;
	**cur = *node;
	cur = &(*cur)->next;
	*cur = 0;
    }
    return my_root;
}

static void PrintMember(pEnv env, Node *cur, int list, int *pindex, FILE *fp)
{
    char *name;
    int offset, flags, index = *pindex;

    if (!cur)
	return;
    fprintf(fp, "{");
    switch (cur->op) {
    case USR_ :
	offset = cur->u.num;
	if (dict_body(env, offset) == 0) {
	    fprintf(fp, ".u.str=\"%s\",", dict_name(env, offset));
	    fprintf(fp, ".op=SYMBOL_");
	} else {
	    flags = dict_flags(env, offset);
	    name = dict_nickname(env, offset);
	    if ((flags & IS_BUILTIN) == 0)
		if ((flags & IS_DECLARED) == 0) {
		    flags |= IS_DECLARED;
		    fprintf(declfp, "void do_%s(pEnv env);", name);
		}
	    dict_setflags(env, offset, flags |= IS_USED);
	    fprintf(fp, ".u.proc=do_%s,", name);
	    fprintf(fp, ".op=ANON_FUNCT_");
	}
	break;
    case ANON_FUNCT_ :
	fprintf(fp, ".u.proc=do_%s,", procname(cur->u.proc));
	fprintf(fp, ".op=ANON_FUNCT_");
	break;
    case BOOLEAN_ :
	fprintf(fp, ".u.num=%d,", cur->u.num != 0);
	fprintf(fp, ".op=BOOLEAN_");
	break;
    case CHAR_ :
	fprintf(fp, ".u.num=%d,", (int)cur->u.num);
	fprintf(fp, ".op=CHAR_");
	break;
    case INTEGER_ :
	fprintf(fp, ".u.num=%ld,", (long)cur->u.num);
	fprintf(fp, ".op=INTEGER_");
	break;
    case SET_ :
	fprintf(fp, ".u.num=%lu,", (unsigned long)cur->u.set);
	fprintf(fp, ".op=SET_");
	break;
    case STRING_ :
	fprintf(fp, ".u.str=%s,", PrintString(cur->u.str));
	fprintf(fp, ".op=STRING_");
	break;
    case LIST_ :
	if (cur->u.lis)
	    fprintf(fp, ".u.lis=L%d+%d,", list, index + 1);
	fprintf(fp, ".op=LIST_");
	if (cur->next)
	   fprintf(fp, ",.next=L%d+%d", list, index + 1 + ListLeng(cur->u.lis));
	fprintf(fp, "},\n");
	*pindex = index + 1;
	for (cur = cur->u.lis; cur; cur = cur->next)
	    PrintMember(env, cur, list, pindex, fp);
	return;
    case FLOAT_ :
	fprintf(fp, ".u.dbl=%g,", cur->u.dbl);
	fprintf(fp, ".op=FLOAT_");
	break;
    }
    if (cur->next)
	fprintf(fp, ",.next=L%d+%d", list, index + 1);
    fprintf(fp, "},\n");
    *pindex = index + 1;
}

static int PrintList(pEnv env, Node *cur, FILE *fp)
{
    static int list;
    int leng, index;

    leng = ListLeng(cur);
    fprintf(fp, "static Node L%d[%d] = {\n", ++list, leng);
    for (index = 0; cur; cur = cur->next)
	PrintMember(env, cur, list, &index, fp);
    fprintf(fp, "};\n");
    return list;
}

void printnode(pEnv env, Node *node, FILE *fp)
{
    Node *cur;
    char *name;
    int index, flags;

    switch (node->op) {
    case USR_ :
	index = node->u.num;
	if ((cur = dict_body(env, index)) == 0) {
	    name = dict_name(env, index);
	    fprintf(fp, "PUSH_PTR(SYMBOL_, \"%s\");", name);
	} else {
	    flags = dict_flags(env, index);
	    name = dict_nickname(env, index);
	    if ((flags & IS_BUILTIN) == 0) {
		if ((flags & IS_ACTIVE) == 0 && (flags & IS_USED) == 0) {
		    dict_setflags(env, index, flags | IS_ACTIVE);
		    compile(env, cur);
		    flags = dict_flags(env, index);
		    dict_setflags(env, index, flags & ~IS_ACTIVE);
		    break;
		}
		if ((flags & IS_DECLARED) == 0) {
		    flags |= IS_DECLARED;
		    fprintf(declfp, "void do_%s(pEnv env);", name);
		}
	    }
	    dict_setflags(env, index, flags | IS_USED);
	    fprintf(outfp, "do_%s(env);", name);
	}
	break;
    case BOOLEAN_:
	fprintf(fp, "PUSH_NUM(BOOLEAN_, %d);", node->u.num != 0);
	break;
    case CHAR_:
	fprintf(fp, "PUSH_NUM(CHAR_, %d);", (int)node->u.num);
	break;
    case INTEGER_:
	fprintf(fp, "PUSH_NUM(INTEGER_, %ld);", (long)node->u.num);
	break;
    case SET_:
	fprintf(fp, "PUSH_NUM(SET_, %lu);", (unsigned long)node->u.set);
	break;
    case STRING_:
	name = PrintString(node->u.str);
	fprintf(fp, "PUSH_PTR(STRING_, %s);", name);
	break;
    case LIST_:
	if (!node->u.lis)
	    fprintf(fp, "PUSH_PTR(LIST_, 0);");
	else
	    fprintf(fp, "PUSH_PTR(LIST_, L%d);",
		    PrintList(env, node->u.lis, fp));
	break;
    case FLOAT_:
	fprintf(fp, "PUSH_DBL(%g);", node->u.dbl);
	break;
    case SYMBOL_:
	fprintf(fp, "PUSH_PTR(SYMBOL_, \"%s\");", node->u.str);
	break;
    default:
	execerror("valid datatype", "printnode");
	break;
    }
}

void printstack(pEnv env, FILE *fp)
{
    for (env->stk = reverse(env->stk); env->stk; env->stk = env->stk->next)
	printnode(env, env->stk, fp);
}

void compile(pEnv env, Node *node)
{
    for (printstack(env, outfp); node; node = node->next)
	printnode(env, node, outfp);
}

static void finalise(pEnv env);

static void my_finalise(void)
{
    finalise(environment);
}

void initialise(void)
{
    time_t t = time(0);

    atexit(my_finalise);
    fprintf(declfp = stdout, "/*\n * generated %s */\n", ctime(&t));
    fprintf(declfp, "#define OLD_RUNTIME\n");
    fprintf(declfp, "#include \"runtime.h\"\n");
    initout();
    if ((outfp = nextfile()) == 0) {
	fprintf(stderr, "Failed to open outfile\n");
	exit(1);
    }
    fprintf(outfp, "int yyparse() { pEnv env = environment;");
}

static void declare(pEnv env, FILE *fp)
{
    char *name;
    int i, j, leng, flags;

    leng = dict_size(env);
    for (i = 0; i < leng; i++) {
	flags = dict_flags(env, i);
	if (((flags & IS_ORIGINAL) && !(flags & IS_BUILTIN)) ||
	    ((flags & IS_ORIGINAL) && !(flags & IS_USED))) {
	    fprintf(fp, "#define ");
	    name = dict_nickname(env, i);
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

static void finalise(pEnv env)
{
    Node *body;
    char *name;
    int i, leng, flags, changed;

    fprintf(outfp, "return 0; }");
    do {
	changed = 0;
	for (leng = dict_size(env), i = 0; i < leng; i++) {
	    if ((flags = dict_flags(env, i)) & IS_BUILTIN)
		continue;
	    if ((body = dict_body(env, i)) == 0)
		continue;
	    if ((flags & IS_USED) && (flags & IS_PRINTED) == 0) {
		dict_setflags(env, i, flags | IS_PRINTED);
		name = dict_nickname(env, i);
		if (body->op == USR_)
		    if (!strcmp(name, dict_nickname(env, body->u.num)))
			continue;
		changed = 1;
		fprintf(outfp, "void do_%s(pEnv env) {", name);
		compile(env, body);
		fprintf(outfp, "}");
	    }
	}
    } while (changed);
    printout(declfp);
    closeout();
    fprintf(declfp, "table_t table[] = {");
    iterate_dict_and_write_struct(env, declfp);
    fprintf(declfp, "{ 0, 0 }, };");
    declare(env, declfp);
    fprintf(declfp, "#include \"interp.c\"\n");
}
