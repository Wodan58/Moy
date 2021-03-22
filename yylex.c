/*
    module  : yylex.c
    version : 1.12
    date    : 03/15/21
*/
#include "runtime.h"

YYSTYPE yylval;		/* copy */

static FILE *yyin;
static char line[INPLINEMAX], unget[2];
static int moy_echo, ilevel, linenum, linepos;

static struct {
    FILE *fp;
    char name[ALEN];
    int linenum;
} infile[INPSTACKMAX];

void inilinebuffer(FILE *fp, char *str)
{
    infile[0].fp = yyin = fp;
    strncpy(infile[0].name, str, ALEN);
    infile[0].name[ALEN - 1] = 0;
    infile[0].linenum = 0;
}

void redirect(FILE *fp)
{
    if (infile[ilevel].fp == fp)
	return;
    infile[ilevel].linenum = linenum;
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "redirect");
    infile[++ilevel].fp = yyin = fp;
    infile[ilevel].name[0] = 0;
    infile[ilevel].linenum = linenum = 0;
}

void include(char *filnam)
{
    FILE *fp;

    if ((fp = fopen(filnam, "r")) == 0)
	execerror("valid file name", "include");
    redirect(fp);
    strncpy(infile[ilevel].name, filnam, ALEN);
    infile[ilevel].name[ALEN - 1] = 0;
}

int yywrap(void)
{
    if (yyin != stdin)
	fclose(yyin);
    if (!ilevel)
	exit(0);
    yyin = infile[--ilevel].fp;
    linenum = infile[ilevel].linenum;
    return 0;
}

static void putline(void)
{
    if (moy_echo > 2)
	fprintf(stderr, "%4d", linenum);
    if (moy_echo > 1)
	fputc('\t', stderr);
    fprintf(stderr, "%s", line);
}

static int restofline(void)
{
    int i;

    if (!strncmp(line, "%PUT", 4))
	fprintf(stderr, "%s", &line[4]);
    else {
	for (i = strlen(line) - 1; isspace((int)line[i]); i--)
	    line[i] = '\0';
	for (i = 8; isspace((int)line[i]); i++)
	    ;
	include(&line[i]);
    }
    memset(line, 0, INPLINEMAX);
    return 0;
}

static int getch(void)
{
    int ch;

    if (unget[1]) {
	ch = unget[0];
	unget[0] = unget[1];
	unget[1] = 0;
	return ch;
    }
    if (unget[0]) {
	ch = unget[0];
	unget[0] = 0;
	return ch;
    }
    if (!yyin)
	yyin = stdin;
    if (!line[linepos]) {
	while (!fgets(line, INPLINEMAX, yyin))
	    yywrap();
	linenum++;
	linepos = 0;
	if (moy_echo)
	    putline();
    }
    return line[linepos++];
}

static void ungetch(int ch)
{
    if (unget[0])
	unget[1] = unget[0];
    unget[0] = ch;
}

static int specialchar(void)
{
    int ch, num;

    if (strchr("\"'\\btnvfr", ch = getch()))
	switch (ch) {
	case 'b':
	    return 8;
	case 't':
	    return 9;
	case 'n':
	    return 10;
	case 'v':
	    return 11;
	case 'f':
	    return 12;
	case 'r':
	    return 13;
	default:
	    return ch;
	}
    if (!isdigit(ch))
	return ch;
    num = 10 * (ch - '0');
    ch = getch();
    if (!isdigit(ch))
	yyerror("digit expected");
    num += ch - '0';
    num *= 10;
    ch = getch();
    if (!isdigit(ch))
	yyerror("digit expected");
    num += ch - '0';
    return num;
}

static int read_char(pEnv env)
{
    int ch;

    if ((ch = getch()) == '\\')
	ch = specialchar();
    env->yylval.num = ch;
    return CHAR_;
}

static int read_string(pEnv env)
{
    int ch, i = 0;
    char string[INPLINEMAX];

    while ((ch = getch()) != '"') {
	if (ch == '\\')
	    ch = specialchar();
	if (i < INPLINEMAX - 1)
	    string[i++] = ch;
    }
    string[i] = '\0';
    env->yylval.str = GC_strdup(string);
    return STRING_;
}

static int read_number(pEnv env, int ch)
{
    int i = 0, dot = 0;
    char string[INPLINEMAX];

    do {
	if (i < INPLINEMAX - 1)
	    string[i++] = ch;
	ch = getch();
    } while (isdigit(ch));
    if (ch == '.') {
	ch = getch();
	dot = 1;
    }
    if (isdigit(ch)) {
	if (i < INPLINEMAX - 1)
	    string[i++] = '.';
	do {
	    if (i < INPLINEMAX - 1)
		string[i++] = ch;
	    ch = getch();
	} while (isdigit(ch));
	if (ch == 'e' || ch == 'E') {
	    if (i < INPLINEMAX - 1)
		string[i++] = ch;
	    if ((ch = getch()) == '-' || ch == '+') {
		if (i < INPLINEMAX - 1)
		    string[i++] = ch;
		ch = getch();
	    }
	    while (isdigit(ch)) {
		if (i < INPLINEMAX - 1)
		    string[i++] = ch;
		ch = getch();
	    }
	}
	ungetch(ch);
	string[i] = '\0';
	env->yylval.dbl = strtod(string, NULL);
	return FLOAT_;
    }
    ungetch(ch);
    if (dot)
	ungetch('.');
    string[i] = '\0';
    env->yylval.num = strtol(string, NULL, 0);
    return INTEGER_;
}

static int read_symbol(pEnv env, int ch)
{
    int i = 0;
    char string[INPLINEMAX];

    do {
	if (i < INPLINEMAX - 1)
	    string[i++] = ch;
	ch = getch();
    } while (isalnum(ch) || strchr("-=_", ch) ||
	    (i == 1 && strchr("*+/<>", ch)));
    if (ch == '.') {
	if (strchr("-=_", ch = getch()) || isalnum(ch)) {
	    if (i < INPLINEMAX - 1)
		string[i++] = '.';
	    do {
		if (i < INPLINEMAX - 1)
		    string[i++] = ch;
		ch = getch();
	    } while (isalnum(ch) || strchr("-=_", ch));
	} else {
	    ungetch(ch);
	    ch = '.';
	}
    }
    ungetch(ch);
    string[i] = '\0';
    if (isupper((int)string[1])) {
	if (!strcmp(string, "%PUT") || !strcmp(string, "%INCLUDE"))
	    return restofline();
	if (!strcmp(string, "END"))
	    return END;
	if (!strcmp(string, "LIBRA") || !strcmp(string, "DEFINE") ||
	    !strcmp(string, "IN") || !strcmp(string, "PUBLIC"))
	    return JPUBLIC;
	if (!strcmp(string, "HIDE") || !strcmp(string, "PRIVATE"))
	    return JPRIVATE;
	if (!strcmp(string, "MODULE"))
	    return MODULE;
    }
    if (!strcmp(string, "=="))
	return JEQUAL;
    if (!strcmp(string, "true")) {
	env->yylval.num = 1;
	return BOOLEAN_;
    }
    if (!strcmp(string, "false")) {
	env->yylval.num = 0;
	return BOOLEAN_;
    }
    if (!strcmp(string, "maxint")) {
	env->yylval.num = MAXINT_;
	return INTEGER_;
    }
    env->yylval.str = GC_strdup(string);
    return SYMBOL_;
}

static int read_end(pEnv env)
{
    int ch;

    ungetch(ch = getch());
    if (isalnum(ch) || strchr("-*+/<=>_", ch))
	return read_symbol(env, '.');
    return END;
}

static int read_minus(pEnv env)
{
    int ch;

    ungetch(ch = getch());
    if (isdigit(ch))
	return read_number(env, '-');
    return read_symbol(env, '-');
}

static int read_octal(pEnv env)
{
    int ch, i = 0;
    char string[INPLINEMAX];

    string[i++] = '0';
    if ((ch = getch()) == 'x' || ch == 'X') {
	do {
	    if (i < INPLINEMAX - 1)
		string[i++] = ch;
	    ch = getch();
	} while (isxdigit(ch));
    } else if (isdigit(ch)) {
	while (ch >= '0' && ch <= '7') {
	    if (i < INPLINEMAX - 1)
		string[i++] = ch;
	    ch = getch();
	}
    }
    string[i] = '\0';
    ungetch(ch);
    if (ch == '.')
	return '0';
    env->yylval.num = strtol(string, NULL, 0);
    return INTEGER_;
}

static int getsym(pEnv env)
{
    int ch;

start:
    while ((ch = getch()) <= ' ')
	;
    switch (ch) {
    case '(':
	if ((ch = getch()) == '*') {
	    ch = getch();
	    do
		while (ch != '*')
		    ch = getch();
	    while ((ch = getch()) != ')');
	    goto start;
	}
	ungetch(ch);
	return '(';
    case '#':
	while ((ch = getch()) != '\n')
	    ;
	goto start;
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case ';':
	return ch;
    case '.':
	return read_end(env);
    case '\'':
	return read_char(env);
    case '"':
	return read_string(env);
    case '-':
	return read_minus(env);
    case '0':
	if ((ch = read_octal(env)) != '0')
	    return ch;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
	return read_number(env, ch);
    default:
	if ((ch = read_symbol(env, ch)) == 0)
	    goto start;
	return ch;
    }
}

int yylex(void)
{
    int rv;
    pEnv env = environment;

    rv = getsym(env);
    yylval = env->yylval;
    return rv;
}

int getechoflag(void)
{
    return moy_echo;
}

void setechoflag(int flag)
{
    moy_echo = flag;
}

int yyerror(char *str)
{
    int i, pos;

    fprintf(stderr, "\nIn file %s line %d:\n", infile[ilevel].name, linenum);
    putline();
    if (moy_echo > 1)
	fputc('\t', stderr);
    for (i = 0, pos = linepos - 1; i < pos; i++)
	fputc(' ', stderr);
    fprintf(stderr, "^\n\t%s\n\n", str);
    execerror(0, 0);
    return 0;
}
