/*
    module  : compile.c
    version : 1.36
    date    : 05/19/19
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
    ptr = malloc_sec(leng + 1);
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
	if (new_version)
	    fprintf(fp, "cur = joy_code();");
	switch (cur->op) {
	case USR_ :
	    index = cur->u.num;
	    if (dict_body(index) == 0) {
		name = dict_name(index);
		if (new_version)
		    fprintf(fp, "cur->str = \"%s\";", name);
		else
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
		if (new_version) {
		    if (!strcmp(name, "pop"))
			fprintf(fp, "cur->fun = (proc_t)do_pop;");
		    else
			fprintf(fp, "cur->fun = do_%s;", name);
		} else
		    fprintf(fp, "list = ANON_FUNCT_NEWNODE(do_%s, list);", name);
	    }
	    break;
	case ANON_FUNCT_ :
	    name = procname(cur->u.proc);
	    fprintf(fp, "list = ANON_FUNCT_NEWNODE(do_%s, list);", name);
	    break;
	case BOOLEAN_ :
	    if (new_version)
		fprintf(fp, "cur->num = %d;", cur->u.num != 0);
	    else
		fprintf(fp, "list = BOOLEAN_NEWNODE(%d, list);", cur->u.num != 0);
	    break;
	case CHAR_ :
	    if (new_version)
		fprintf(fp, "cur->num = %d;", (int)cur->u.num);
	    else
		fprintf(fp, "list = CHAR_NEWNODE(%d, list);", (int)cur->u.num);
	    break;
	case INTEGER_ :
	    if (new_version)
		fprintf(fp, "cur->num = " PRINT_NUM ";", cur->u.num);
	    else
		fprintf(fp, "list = INTEGER_NEWNODE(" PRINT_NUM ", list);",
			cur->u.num);
	    break;
	case SET_ :
	    if (new_version)
		fprintf(fp, "cur->num = " PRINT_SET ";", cur->u.set);
	    else
		fprintf(fp, "list = SET_NEWNODE(" PRINT_SET ", list);",
			cur->u.set);
	    break;
	case STRING_ :
	    if (!cur->u.str) {
		if (new_version)
		    fprintf(fp, "cur->str = 0;");
		else
		    fprintf(fp, "list = STRING_NEWNODE(0, list);");
	    } else {
		name = PrintString(cur->u.str);
		if (new_version)
		    fprintf(fp, "cur->str = %s;", name);
		else
		    fprintf(fp, "list = STRING_NEWNODE(%s, list);", name);
	    }
	    break;
	case LIST_ :
	    if (!cur->u.lis) {
		if (new_version)
		    fprintf(fp, "cur->list = 0;");
		else
		    fprintf(fp, "list = LIST_NEWNODE(0, list);");
	    } else {
		if (new_version) {
		    fprintf(fp, "{ code_t *cur, *list = 0;");
		    printlist(cur->u.lis, fp);
		    fprintf(fp, "do_push((node_t)list); }");
		    fprintf(fp, "cur->list = (code_t *)do_pop();");
		} else {
		    fprintf(fp, "{ Node *list = 0;");
		    printlist(cur->u.lis, fp);
		    fprintf(fp, "PUSH(LIST_, list); }");
		    fprintf(fp, "list = LIST_NEWNODE(stk->u.lis, list);");
		    fprintf(fp, "POP(stk);");
		}
	    }
	    break;
	case FLOAT_ :
	    if (new_version)
		fprintf(fp, "cur->dbl = %g;", cur->u.dbl);
	    else
		fprintf(fp, "list = FLOAT_NEWNODE(%g, list);", cur->u.dbl);
	    break;
	default :
	    execerror("valid datatype", "printlist");
	    break;
	}
	if (new_version) {
	    fprintf(fp, "cur->next = list;");
	    fprintf(fp, "list = cur;");
	}
    }
}

static void PrintMember(Node *cur, unsigned list, unsigned *pindex, FILE *fp)
{
    char *name;
    int offset;
    unsigned flags, index = *pindex;

    if (!cur)
	return;
    fprintf(fp, "{");
    switch (cur->op) {
    case USR_ :
	offset = cur->u.num;
	if (dict_body(offset) == 0) {
	    fprintf(fp, ".u.str=\"%s\",", dict_name(offset));
	    fprintf(fp, ".op=SYMBOL_");
	} else {
	    flags = dict_flags(offset);
	    name = dict_nickname(offset);
	    if ((flags & IS_BUILTIN) == 0) {
		if ((flags & IS_DECLARED) == 0) {
		    flags |= IS_DECLARED;
		    fprintf(declfp, "void do_%s(void);", name);
		}
	    }
	    dict_setflags(offset, flags |= IS_USED);
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
	fprintf(fp, ".u.num=" PRINT_NUM ",", cur->u.num);
	fprintf(fp, ".op=INTEGER_");
	break;
    case SET_ :
	fprintf(fp, ".u.num=" PRINT_SET ",", cur->u.set);
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
	    PrintMember(cur, list, pindex, fp);
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

static unsigned PrintList(Node *cur, FILE *fp)
{
    static unsigned list;
    unsigned leng, index;

    leng = ListLeng(cur);
    fprintf(fp, "static Node L%d[%d] = {\n", ++list, leng);
    for (index = 0; cur; cur = cur->next)
	PrintMember(cur, list, &index, fp);
    fprintf(fp, "};\n");
    return list;
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
	    if (new_version)
		fprintf(fp, "do_push((node_t)\"%s\");", name);
	    else
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
	if (new_version)
	    fprintf(fp, "do_push(%d);", node->u.num != 0);
	else
	    fprintf(fp, "PUSH(BOOLEAN_, %d);", node->u.num != 0);
	break;
    case CHAR_:
	if (new_version)
	    fprintf(fp, "do_push(%d);", (int)node->u.num);
	else
	    fprintf(fp, "PUSH(CHAR_, %d);", (int)node->u.num);
	break;
    case INTEGER_:
	if (new_version)
	    fprintf(fp, "do_push(" PRINT_NUM ");", node->u.num);
	else
	    fprintf(fp, "PUSH(INTEGER_, " PRINT_NUM ");", node->u.num);
	break;
    case SET_:
	if (new_version)
	    fprintf(fp, "do_push(" PRINT_SET ");", node->u.set);
	else
	    fprintf(fp, "PUSH(SET_, " PRINT_SET ");", node->u.set);
	break;
    case STRING_:
	name = PrintString(node->u.str);
	if (new_version)
	    fprintf(fp, "do_push((node_t)%s);", name);
	else
	    fprintf(fp, "PUSH(STRING_, %s);", name);
	break;
    case LIST_:
	if (!node->u.lis) {
	    if (new_version)
		fprintf(fp, "do_push(0);");
	    else
		fprintf(fp, "PUSH(LIST_, 0);");
	} else {
	    if (new_version) {
		fprintf(fp, "{ code_t *cur, *list = 0;");
		printlist(node->u.lis, fp);
		fprintf(fp, "do_push((node_t)list); }");
	    } else if (old_version) {
		fprintf(fp, "PUSH(LIST_, L%d);", PrintList(node->u.lis, fp));
	    } else {
		fprintf(fp, "{ Node *list = 0;");
		printlist(node->u.lis, fp);
		fprintf(fp, "PUSH(LIST_, list); }");
	    }
	}
	break;
    case FLOAT_:
	if (new_version)
	    fprintf(fp, "do_push_dbl(%g);", node->u.dbl);
	else
	    fprintf(fp, "DBL_PUSH((real_t)%g);", node->u.dbl);
	break;
    case SYMBOL_:
	if (new_version)
	    fprintf(fp, "do_push((node_t)\"%s\");", node->u.str);
	else
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
    declfp = stdout;
    fprintf(declfp, "/*\n * generated %s */\n", ctime(&t));
    initout();
    outfp = nextfile();
    if (new_version)
	fprintf(outfp, "\n#include \"builtin.c\"\n");
    else
	fprintf(outfp, "\n#include \"interp1.c\"\n");
    fprintf(outfp, "\nint/* MAIN */%s(int argc, char **argv) {", mainfunc);
    if (new_version)
	fprintf(outfp, "joy_init(argc, argv);");
    else
	fprintf(outfp, "initsym(argc, argv);");
}

void declare(void)
{
    char *name;
    unsigned flags;
    int i, j, leng;

    leng = dict_size();
    for (i = 0; i < leng; i++) {
	flags = dict_flags(i);
	if (((flags & IS_ORIGINAL) && !(flags & IS_BUILTIN)) ||
	    ((flags & IS_ORIGINAL) && !(flags & IS_USED))) {
	    fprintf(declfp, "#define ");
	    name = dict_nickname(i);
	    for (j = 0; name[j]; j++)
		fputc(toupper(name[j]), declfp);
	    fprintf(declfp, "_X\n");
	}
    }
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
    declare();
    printout();
    closeout();
    printf("table_t table[] = {");
    iterate_dict_and_write_struct();
    printf("{ 0, 0 }, };\n");
}
