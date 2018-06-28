/*
    module  : print.c
    version : 1.19
    date    : 06/28/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

char *opername(int num)
{
    static char *names[] = {
"DO_NOTHING", "DO_FALSE", "DO_TRUE", "DO_MAXINT", "DO_SETSIZE", "DO_STACK",
"DO_SYMTABMAX", "DO_SYMTABINDEX", "DO_DUMP", "DO_CONTS", "DO_AUTOPUT",
"DO_UNDEFERROR", "DO_UNDEFS", "DO_ECHO", "DO_CLOCK", "DO_TIME", "DO_RAND",
"DO_MEMORYMAX", "DO_STDIN", "DO_STDOUT", "DO_STDERR", "DO_ID", "DO_DUP",
"DO_OVER", "DO_PICK", "DO_SWAP", "DO_ROLLUP", "DO_ROLLDOWN", "DO_ROTATE",
"DO_POPD", "DO_MUL", "DO_PLUS", "DO_DUPD", "DO_MINUS", "DO_STOP", "DO_DIVIDE",
"DO_SWAPD", "DO_ROLLUPD", "DO_ROLLDOWND", "DO_ROTATED", "DO_POP", "DO_CHOICE",
"DO_OR", "DO_XOR", "DO_AND", "DO_NOT", "DO_REM", "SEMI", "DO_LESS", "DO_EQL",
"DO_GREATER", "DO_DIV", "DO_SIGN", "DO_NEG", "DO_ORD", "DO_CHR", "DO_ABS",
"DO_ACOS", "DO_ASIN", "DO_ATAN", "DO_ATAN2", "DO_CEIL", "DO_COS", "DO_COSH",
"DO_EXP", "DO_FLOOR", "DO_ROUND", "DO_FREXP", "DO_LDEXP", "DO_LOG", "DO_LOG10",
"DO_MODF", "DO_POW", "DO_SIN", "DO_SINH", "DO_SQRT", "DO_TAN", "DO_TANH",
"DO_TRUNC", "LBRACK", "DO_LOCALTIME", "RBRACK", "DO_GMTIME", "DO_MKTIME",
"DO_STRFTIME", "DO_STRTOL", "DO_STRTOD", "DO_FORMAT", "DO_FORMATF", "DO_SRAND",
"DO_PRED", "DO_SUCC", "DO_MAX", "DO_MIN", "DO_FCLOSE", "DO_FEOF", "DO_FERROR",
"DO_FFLUSH", "DO_FGET", "DO_FGETCH", "DO_FGETS", "DO_FOPEN", "DO_FREAD",
"DO_FWRITE", "DO_FREMOVE", "DO_FRENAME", "DO_FILETIME", "DO_FPUT", "DO_FPUTCH",
"DO_FPUTCHARS", "DO_FPUTSTRING", "LBRACE", "DO_FSEEK", "RBRACE", "DO_FTELL",
"DO_UNSTACK", "DO_CONS", "DO_SWONS", "DO_FIRST", "DO_REST", "DO_COMPARE",
"DO_INDEX", "DO_AT", "DO_OF", "DO_SIZE", "DO_CASTING", "DO_OPCASE", "DO_CASE",
"DO_UNCONS", "DO_UNSWONS", "DO_DROP", "DO_TAKE", "DO_CONCAT", "DO_ENCONCAT",
"DO_NAME", "DO_INTERN", "DO_BODY", "DO_NULL", "DO_SMALL", "DO_GEQL", "DO_LEQL",
"DO_NEQL", "DO_EQUAL", "DO_HAS", "DO_IN", "DO_SAMETYPE", "DO_INTEGER",
"DO_CHAR", "DO_LOGICAL", "DO_SET", "DO_STRING", "DO_LIST", "DO_LEAF", "DO_USER",
"DO_FLOAT", "DO_FILE", "DO_I", "DO_X", "DO_DIP", "DO_APP1", "DO_APP11",
"DO_APP12", "DO_CONSTRUCT", "DO_NULLARY", "DO_UNARY", "DO_UNARY2", "DO_UNARY3",
"DO_UNARY4", "DO_APP2", "DO_APP3", "DO_APP4", "DO_BINARY", "DO_TERNARY",
"DO_CLEAVE", "DO_BRANCH", "DO_IFTE", "DO_IFINTEGER", "DO_IFCHAR",
"DO_IFLOGICAL", "DO_IFSET", "DO_IFSTRING", "DO_IFLIST", "DO_IFFLOAT",
"DO_IFFILE", "DO_COND", "DO_WHILE", "DO_LINREC", "DO_TAILREC", "DO_BINREC",
"DO_GENREC", "DO_CONDNESTREC", "DO_CONDLINREC", "DO_STEP", "DO_FOLD", "DO_MAP",
"DO_TIMES", "DO_INFRA", "DO_PRIMREC", "DO_FILTER", "DO_SPLIT", "DO_SOME",
"DO_ALL", "DO_TREESTEP", "DO_TREEREC", "DO_TREEGENREC", "DO_HELP", "DO_HELP1",
"DO_HELPDETAIL", "DO_MANUAL", "DO_HTML_MANUAL", "DO_LATEX_MANUAL",
"DO_MANUAL_LIST", "DO_SETTRACEGC", "DO_SETAUTOPUT", "DO_SETUNDEFERROR",
"DO_SETECHO", "DO_GC", "DO_SYSTEM", "DO_GETENV", "DO_ARGV", "DO_ARGC",
"DO_MEMORYINDEX", "DO_GET", "DO_GETCH", "DO_PUT", "DO_PUTCH", "DO_PUTCHARS",
"DO_INCLUDE", "DO_ABORT", "DO_QUIT"
    };
    static char str[ALEN];
    int i;
    char *ptr;

    if (num < DO_NOTHING || num > DO_QUIT) {
	sprintf(str, "'%x", num);
	return str;
    }
    for (i = 0, ptr = names[num - DO_NOTHING] + 3; ptr[i]; i++)
	str[i] = tolower(ptr[i]);
    str[i] = 0;
    return str;
}

char *printname(int num)
{
    switch (num) {
    case DO_PLUS:
	return "+";
    case DO_MINUS:
	return "-";
    case DO_MUL:
	return "*";
    case DO_DIVIDE:
	return "/";
    case DO_GEQL:
	return ">=";
    case DO_GREATER:
	return ">";
    case DO_LEQL:
	return "<=";
    case DO_LESS:
	return "<";
    case DO_NEQL:
	return "!=";
    case DO_EQL:
	return "=";
    }
    return opername(num);
}

static char *opername2(char *str)
{
    if (!strcmp(str, "plus"))
	return "+";
    if (!strcmp(str, "minus"))
	return "-";
    if (!strcmp(str, "mul"))
	return "*";
    if (!strcmp(str, "divide"))
	return "/";
    if (!strcmp(str, "geql"))
	return ">=";
    if (!strcmp(str, "greater"))
	return ">";
    if (!strcmp(str, "leql"))
	return "<=";
    if (!strcmp(str, "less"))
	return "<";
    if (!strcmp(str, "neql"))
	return "!=";
    if (!strcmp(str, "eql"))
	return "=";
    return str;
}

static char *symname(char *str)
{
    char *ptr;
    unsigned i;

    if (strchr(ptr = str, '_')) {
	ptr = GC_strdup(str);
	for (i = 0; ptr[i]; i++)
	    if (ptr[i] == '_')
		ptr[i] = '-';
    }
    return opername2(ptr);
}

void writefactor(Node *node, FILE *stm)
{
    char *ptr;
    long_t set;
    unsigned i, j;

    switch (node->op) {
    case BOOLEAN_:
	fprintf(stm, "%s", node->u.num ? "true" : "false");
	break;
    case CHAR_:
	if (node->u.num == '\n')
	    fprintf(stm, "'\\n");
	else
	    fprintf(stm, "'%c", (int)node->u.num);
	break;
    case INTEGER_:
	fprintf(stm, "%lld", (long long)node->u.num);
	break;
    case SET_:
	fprintf(stm, "{");
	for (set = node->u.set, i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	    if (set & j) {
		fprintf(stm, "%d", i);
		if ((set &= ~j) == 0)
		    break;
		fprintf(stm, " ");
	    }
	fprintf(stm, "}");
	break;
    case STRING_:
	fputc('"', stm);
	for (ptr = node->u.str; *ptr; ptr++) {
	    if (*ptr == '"' || *ptr == '\\' || *ptr == '\n')
		fputc('\\', stm);
	    fputc(*ptr == '\n' ? 'n' : *ptr, stm);
	}
	fputc('"', stm);
	break;
    case LIST_:
	fprintf(stm, "%s", "[");
	writeterm(node->u.lis, stm);
	fprintf(stm, "%s", "]");
	break;
    case FLOAT_:
	fprintf(stm, "%g", node->u.dbl);
	break;
    case FILE_:
	if (!node->u.fil)
	    fprintf(stm, "file:NULL");
	else if (node->u.fil == stdin)
	    fprintf(stm, "file:stdin");
	else if (node->u.fil == stdout)
	    fprintf(stm, "file:stdout");
	else if (node->u.fil == stderr)
	    fprintf(stm, "file:stderr");
	else
	    fprintf(stm, "file:%p", node->u.fil);
	break;
    case USR_:
	fprintf(stm, "%s", dict_descr(node->u.num));
	break;
    case ANON_FUNCT_:
	if ((ptr = procname(node->u.proc)) != 0)
	    fprintf(stm, "%s", ptr);
	else
	    fprintf(stm, "%p", node->u.proc);
	break;
    case SYMBOL_:
	fprintf(stm, "%s", symname(node->u.str));
	break;
    default:
	fprintf(stm, "%s", ptr = printname(node->op));
	if (*ptr == '\'') {
	    fprintf(stderr, "unknown, %s\n", ptr);
	    exit(1);
	}
	break;
    }
}

void writeterm(Node *code, FILE *stm)
{
    while (code) {
	writefactor(code, stm);
	if (code->next)
	    putc(' ', stm);
	code = code->next;
    }
}

void writestack(Node *code, FILE *stm)
{
    if (code != memory) {
	if (code == code->next)
	    fprintf(stm, "ERROR ");
	else {
	    writestack(code->next, stm);
	    putc(' ', stm);
	}
	writefactor(code, stm);
    }
}
