/*
    module  : yylex.c
    version : 1.18
    date    : 07/04/22
*/
#include "runtime.h"

extern YYSTYPE yylval;		/* runtime.c */

FILE *yyin;			/* initsym.c */

static char line[INPLINEMAX + 1], unget[2];
static int echoflag, ilevel, linenum, linepos;

static struct {
    FILE *fp;
#if 0
    char name[ALEN];
#endif
    int linenum;
} infile[INPSTACKMAX];

/*
    inilinebuffer - initialise the stack of input files. Filename is not used.
		    Also initializes yyin. Multiple calls to inilinebuffer are
		    allowed.
*/
void inilinebuffer(void)
{
    infile[0].fp = yyin = stdin;
#if 0
    strncpy(infile[0].name, name, ALEN);
    infile[0].name[ALEN - 1] = 0;
#endif
    infile[0].linenum = 0;
}

/*
    redirect - change input to a new file.
*/
static void redirect(pEnv env, FILE *fp)
{
    infile[ilevel].linenum = linenum;
    if (ilevel + 1 == INPSTACKMAX)
	execerror(env, "fewer include files", "redirect");
    infile[++ilevel].fp = yyin = fp;
#if 0
    strncpy(infile[ilevel].name, name, ALEN);
    infile[ilevel].name[ALEN - 1] = 0;
#endif
    infile[ilevel].linenum = linenum = 0;
}

/*
    include - insert the contents of a file in the input.
*/
void include(pEnv env, char *name, int error)
{
    FILE *fp;

    if ((fp = fopen(name, "r")) != 0)
        redirect(env, fp);
    else if (error)
        execerror(env, "valid file name", "include");
}

/*
    yywrap - end of file processing, returning to a previous input.
*/
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

/*
    putline - echo an input line.
*/
static void putline(void)
{
    if (echoflag > 2)
	printf("%4d", linenum);
    if (echoflag > 1)
	putchar('\t');
    printf("%s", line);
}

/*
    restofline - handle %PUT and %INCLUDE.
*/
static int restofline(pEnv env)
{
    if (!strncmp(line, "%PUT", 4))
	fprintf(stderr, "%s", &line[4]);
    else
	include(env, DelSpace(line + 8), 1);
    memset(line, 0, sizeof(line));
    return 0;
}

/*
    getch - return one character.
*/
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
    if (!line[linepos]) {
again:
	if (fgets(line, INPLINEMAX, yyin))
	    linenum++;
	else {
	    yywrap();
	    goto again;
	}
	linepos = 0;
	if (echoflag)
	    putline();
    }
    return line[linepos++];
}

/*
    ungetch - stack an unwanted character. A maximum of 2 characters need to
	      be remembered here.
*/
static void ungetch(int ch)
{
    if (unget[0])
	unget[1] = unget[0];
    unget[0] = ch;
}

/*
    specialchar - handle character escape sequences.
*/
static int specialchar(pEnv env)
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
	yyerror(env, "digit expected");
    num += ch - '0';
    num *= 10;
    ch = getch();
    if (!isdigit(ch))
	yyerror(env, "digit expected");
    num += ch - '0';
    return num;
}

/*
    read_char - read one character and return type and value.
*/
static int read_char(pEnv env)
{
    int ch;

    if ((ch = getch()) == '\\')
	ch = specialchar(env);
    env->yylval.num = ch;
    return CHAR_;
}

/*
    read_string - read a string and return type and value.
*/
static int read_string(pEnv env)
{
    int ch, i = 0;
    char string[INPLINEMAX + 1];

    while ((ch = getch()) != '"') {
	if (ch == '\\')
	    ch = specialchar(env);
	if (i < INPLINEMAX)
	    string[i++] = ch;
    }
    string[i] = '\0';
    env->yylval.str = GC_strdup(string);
    return STRING_;
}

/*
    read_number - read a number and return type and value.
*/
static int read_number(pEnv env, int ch)
{
    int i = 0, dot = 0;
    char string[INPLINEMAX + 1];

    do {
	if (i < INPLINEMAX)
	    string[i++] = ch;
	ch = getch();
    } while (isdigit(ch));
    if (ch == '.') {
	ch = getch();
	dot = 1;
    }
    if (isdigit(ch)) {
	if (i < INPLINEMAX)
	    string[i++] = '.';
	do {
	    if (i < INPLINEMAX)
		string[i++] = ch;
	    ch = getch();
	} while (isdigit(ch));
	if (ch == 'e' || ch == 'E') {
	    if (i < INPLINEMAX)
		string[i++] = ch;
	    if ((ch = getch()) == '-' || ch == '+') {
		if (i < INPLINEMAX)
		    string[i++] = ch;
		ch = getch();
	    }
	    while (isdigit(ch)) {
		if (i < INPLINEMAX)
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

/*
    read_symbol - read a symbol and return type and value.
*/
static int read_symbol(pEnv env, int ch)
{
    int i = 0;
    char string[INPLINEMAX + 1];

    do {
	if (i < INPLINEMAX)
	    string[i++] = ch;
	ch = getch();
    } while (isalnum(ch) || strchr("-=_", ch));
    if (ch == '.') {
	if (strchr("-=_", ch = getch()) || isalnum(ch)) {
	    if (i < INPLINEMAX)
		string[i++] = '.';
	    do {
		if (i < INPLINEMAX)
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
	    return restofline(env);
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
    return USR_;
}

/*
    read_end - read and return the end symbol.
*/
static int read_end(pEnv env)
{
    int ch;

    ungetch(ch = getch());
    if (isalnum(ch) || ch == '_')
	return read_symbol(env, '.');
    return END;
}

/*
    read_minus - read either a number or a symbol.
*/
static int read_minus(pEnv env)
{
    int ch;

    ungetch(ch = getch());
    if (isdigit(ch))
	return read_number(env, '-');
    return read_symbol(env, '-');
}

/*
    read_octal - read and return an octal or hexadecimal number.
*/
static int read_octal(pEnv env)
{
    int ch, i = 0;
    char string[INPLINEMAX + 1];

    string[i++] = '0';
    if ((ch = getch()) == 'x' || ch == 'X') {
	do {
	    if (i < INPLINEMAX)
		string[i++] = ch;
	    ch = getch();
	} while (isxdigit(ch));
    } else if (isdigit(ch)) {
	while (ch >= '0' && ch <= '7') {
	    if (i < INPLINEMAX)
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

/*
    getsym - lexical analyzer, filling yylval and returning the token type.
*/
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

/*
    yylex - lexical analyzer, filling yylval and returning the token type.
*/
int yylex(pEnv env)
{
    int rv;

    rv = getsym(env);
    yylval = env->yylval;
    return rv;
}

/*
    getechoflag - function that accesses the echo flag.
*/
int getechoflag(void)
{
    return echoflag;
}

/*
    setechoflag - function that sets the echo flag.
*/
void setechoflag(int flag)
{
    echoflag = flag;
}

/*
    yyerror - error processing during source file reads.
*/
int yyerror(pEnv env, char *str)
{
    int i, pos;

    if (!echoflag)
        putline();
    if (echoflag > 1)
	fputc('\t', stderr);
    for (i = 0, pos = linepos - 2; i < pos; i++)
	fputc(' ', stderr);
    fprintf(stderr, "^\n\t%s\n\n", str);
    abortexecution();
    return 0;
}
