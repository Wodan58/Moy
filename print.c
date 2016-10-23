/*
    module  : print.c
    version : 1.12
    date    : 10/17/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"
#include "globals1.h"
#include "compile.h"

#define P(x)		utstring_printf(str, x)
#define Q(x, y)		utstring_printf(str, x, y)
#define R(x, y, z)	utstring_printf(str, x, y, z)
#define S(x, y, z, w)	utstring_printf(str, x, y, z, w)

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

char *CorrectOpername(int op)
{
    char *str = opername(op);

    if (!isalpha((int) *str))
	switch (*str) {
	case '!':
	    if (str[1] == '=')
		return "neql";
	    break;
	case '*':
	    return "mul";
	case '+':
	    return "plus";
	case '-':
	    return "minus";
	case '/':
	    return "divide";
	case '<':
	    if (str[1] == '=')
		return "leql";
	    if (!str[1])
		return "less";
	    break;
	case '=':
	    return "eql";
	case '>':
	    if (str[1] == '=')
		return "geql";
	    if (!str[1])
		return "greater";
	    break;
	}
    return str;
}

size_t StringLen(char *str)
{
    size_t i;

    for (i = 2; *str; i++, str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13))
	    i++;
	else if (iscntrl((int) *str))
	    i += 3;
    return i;
}

void StringPrint(char *ptr, char *str)
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

char *PrintString(char *str)
{
    char *ptr;
    size_t leng;

    leng = StringLen(str);
    ptr = malloc(leng + 1);
    StringPrint(ptr, str);
    return ptr;
}

int ListLen(Node *cur)
{
    int leng;

    for (leng = 0; cur; cur = cur->next) {
	leng++;
	if (cur->op == LIST_)
	    leng += ListLen(cur->u.lis);
    }
    return leng;
}

void PrintMember(Node *cur, int list, int *pindex, UT_string *str)
{
    Entry *sym;
    char *type = 0;
    int index = *pindex;

    if (!cur)
	return;
    switch (cur->op) {
    case USR_:
	sym = cur->u.ent;
	if (!sym->u.body) {
	    R(" [%d].u.str=\"%s\",", index, sym->name);
	    Q(" [%d].op=SYMBOL_,", index);
	} else {
	    if (!sym->uniq)
		sym->uniq = ++identifier;
	    S(" [%d].u.proc=%s_%d,", index, scramble(sym->name), sym->uniq);
	    Q(" [%d].op=ANON_FUNCT_,", index);
	}
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case BOOLEAN_:
	type = "BOOLEAN_";
    case CHAR_:
	if (!type)
	    type = "CHAR_";
    case SET_:
	if (!type)
	    type = "SET_";
    case INTEGER_:
	if (!type)
	    type = "INTEGER_";
	R(" [%d].u.num=%lld,", index, (long long)cur->u.num);
	R(" [%d].op=%s,", index, type);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case FLOAT_:
	R(" [%d].u.dbl=%g,", index, cur->u.dbl);
	Q(" [%d].op=FLOAT_,", index);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case STRING_:
	R(" [%d].u.str=%s,", index, PrintString(cur->u.str));
	Q(" [%d].op=STRING_,", index);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case LIST_:
	if (cur->u.lis)
	    S(" [%d].u.lis=L%d+%d,", index, list, index + 1);
	Q(" [%d].op=LIST_,", index);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index+1 + ListLen(cur->u.ptr));
	P("\n");
	*pindex = index + 1;
	for (cur = cur->u.lis; cur; cur = cur->next)
	    PrintMember(cur, list, pindex, str);
	break;
    default:
	R(" [%d].u.proc=%s_,", index, CorrectOpername(cur->op));
	Q(" [%d].op=ANON_FUNCT_,", index);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    }
}

static int list;

int PrintFirstList(Node *cur, UT_string *str)
{
    int index = 0;

    Q("static Node L%d[1] = {\n", ++list);
    PrintMember(cur, list, &index, str);
    P("};\n");
    return list;
}

void PrintList(Node *cur, UT_string *str)
{
    if (!cur)
	P("PUSH(LIST_, 0);\n");
    else {
	int index = 0, leng = ListLen(cur);
	R("static Node L%d[%d] = {\n", ++list, leng);
	for (; cur; cur = cur->next)
	    PrintMember(cur, list, &index, str);
	Q("};\nPUSH(LIST_, L%d);\n", list);
    }
}

void PrintFactor(Node *node, UT_string *str)
{
    char *name;
    Entry *sym;

    if (!node)
	return;
    switch (node->op) {
    case 0:
	Q("%s", node->u.str);
	break;
    case USR_:
	sym = node->u.ent;
	if (!sym->u.body)
	    Q("PUSH(SYMBOL_, \"%s\");", sym->name);
	else {
	    if (!sym->uniq)
		sym->uniq = ++identifier;
	    name = scramble(sym->name);
	    if (node->unmark)
		R("PUSH(ANON_FUNCT_, %s_%d);", name, sym->uniq);
	    else
		R("%s_%d();", name, sym->uniq);
	}
	break;
    case BOOLEAN_:
	Q("PUSH(BOOLEAN_, %d);", (int)node->u.num);
	break;
    case CHAR_:
	Q("PUSH(CHAR_, %d);", (int)node->u.num);
	break;
    case INTEGER_:
	Q("PUSH(INTEGER_, %lld);", (long long)node->u.num);
	break;
    case FLOAT_:
	Q("FLOAT_PUSH(%g);", node->u.dbl);
	break;
    case STRING_:
	Q("PUSH(STRING_, %s);", PrintString(node->u.str));
	break;
    case SET_:
	Q("PUSH(SET_, %lld);", (long long)node->u.set);
	break;
    case LIST_:
	PrintList(node->u.lis, str);
	break;
    default:
	name = CorrectOpername(node->op);
	if (node->unmark)
	    Q("PUSH(ANON_FUNCT_, %s_);", name);
	else
	    Q("%s_();", name);
	break;
    }
}

void PrintTerm(Node *cur, UT_string *str)
{
    while (cur) {
	PrintFactor(cur, str);
	if ((cur = cur->next) != 0)
	    P(" ");
    }
}
