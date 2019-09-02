/*
    module  : yylex.c
    version : 1.6
    date    : 09/02/19
*/
#include "runtime.h"

static FILE *yyin;
static char line[INPLINEMAX], unget[2];
static int moy_code, moy_echo, lineno, ilevel;

static struct {
    FILE *fp;
    char *name;
    int lineno;
} infile[INPSTACKMAX];

void inilinebuffer(FILE *fp, char *str)
{
    infile[0].fp = yyin = fp;
    infile[0].name = str;
    infile[0].lineno = 0;
}

void redirect(FILE *fp)
{
    infile[ilevel].lineno = lineno;
    if (ilevel + 1 == INPSTACKMAX)
	execerror("fewer include files", "redirect");
    infile[++ilevel].fp = yyin = fp;
    infile[ilevel].name = 0;
    infile[ilevel].lineno = lineno = 0;
}

void include(char *filnam)
{
    FILE *fp;

    if ((fp = fopen(filnam, "r")) == 0)
	execerror("valid file name", "include");
    redirect(fp);
    infile[ilevel].name = ck_strdup(filnam);
}

int yywrap(void)
{
    if (yyin != stdin)
	fclose(yyin);
    if (!ilevel)
	exit(0);
    yyin = infile[--ilevel].fp;
    lineno = infile[ilevel].lineno;
    return 0;
}

static void putline(void)
{
    if (moy_echo > 2)
	fprintf(stderr, "%4d", lineno);
    if (moy_echo > 1)
	fprintf(stderr, "\t");
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
    static int linepos;
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
	lineno++;
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
    int ch;

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
    ch = 10 * (ch - '0');
    ch += getch() - '0';
    ch *= 10;
    ch += getch() - '0';
    return ch;
}

static int read_char(void)
{
    int ch;

    if ((ch = getch()) == '\\')
	ch = specialchar();
    yylval.num = ch;
    return CHAR_;
}

static int read_string(void)
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
    yylval.str = ck_strdup(string);
    return STRING_;
}

static int read_number(int ch)
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
	yylval.dbl = strtod(string, NULL);
	return FLOAT_;
    }
    ungetch(ch);
    if (dot)
	ungetch('.');
    string[i] = '\0';
    yylval.num = strtol(string, NULL, 0);
    return INTEGER_;
}

static int read_symbol(int ch)
{
    int i = 0;
    char string[INPLINEMAX];

    do {
	if (i < INPLINEMAX - 1)
	    string[i++] = ch;
	ch = getch();
    } while (isalnum(ch) || strchr("-=_", ch) || (i == 1 && strchr("*+/<>", ch)));
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
	yylval.num = 1;
	return BOOLEAN_;
    }
    if (!strcmp(string, "false")) {
	yylval.num = 0;
	return BOOLEAN_;
    }
    if (!strcmp(string, "maxint")) {
	yylval.num = MAXINT_;
	return INTEGER_;
    }
    yylval.str = ck_strdup(string);
    return SYMBOL_;
}

static int read_end(void)
{
    int ch;

    ungetch(ch = getch());
    if (isalnum(ch) || strchr("-*+/<=>_", ch))
	return read_symbol('.');
    return END;
}

static int read_minus(void)
{
    int ch;

    ungetch(ch = getch());
    if (isdigit(ch))
	return read_number('-');
    return read_symbol('-');
}

static int read_octal(void)
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
    yylval.num = strtol(string, NULL, 0);
    return INTEGER_;
}

static int getsym(void)
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
	return read_end();
    case '\'':
	return read_char();
    case '"':
	return read_string();
    case '-':
	return read_minus();
    case '0':
	if ((ch = read_octal()) != '0')
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
	return read_number(ch);
    default:
	if ((ch = read_symbol(ch)) == 0)
	    goto start;
	return ch;
    }
}

int yylex(void)
{
    moy_code = getsym();
    return moy_code;
}

int getechoflag(void)
{
    return moy_echo;
}

void setechoflag(int flag)
{
    moy_echo = flag;
}

#ifndef WITHOUT_YYERROR
int yyerror(char *str)
{
    Node node;

    node.u = yylval;
    node.op = moy_code;
    fprintf(stderr, "%s in file %s line %d near ", str, infile[ilevel].name, lineno);
    writefactor(&node, stderr);
    fputc('\n', stderr);
    return 0;
}
#endif
