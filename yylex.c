/*
    module  : yylex.c
    version : 1.1
    date    : 05/19/19
*/
#include "runtime.h"

FILE *yyin = NULL;
static int ch = ' ', dummy;

static void getch(void)
{
    if (!yyin)
	yyin = stdin;
    if ((ch = fgetc(yyin)) == EOF)
	yywrap();
}

int yylex(void)
{
    int i = 0, minus = 0;
    char string[INPLINEMAX];

Start:
    while (ch <= ' ')
	getch();
    switch (ch) {
    case '(':
	getch();
	if (ch == '*') {
	    getch();
	    do {
		while (ch != '*')
		    getch();
		getch();
	    } while (ch != ')');
	    getch();
	    goto Start;
	}
	return '(';
    case '#':
	do
	    getch();
	while (ch != '\n');
	goto Start;
    case ')':
	getch();
	return ')';
    case '[':
	getch();
	return '[';
    case ']':
	getch();
	return ']';
    case '{':
	getch();
	return '{';
    case '}':
	getch();
	return '}';
    case '.':
	getch();
	return '.';
    case ';':
	getch();
	return ';';
    case '"':
	getch();
	while (ch != '"') {
	    string[i++] = ch;
	    getch();
	}
	string[i] = '\0';
	getch();
	yylval.str = strdup(string);
	return STRING_;
    case '-': /* PERHAPS unary minus */
	minus = 1;
	getch();
	/* continue */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
	if (isdigit(ch)) {
	    if (minus)
		string[i++] = '-';
	    do {
		string[i++] = ch;
		getch();
	    } while (isdigit(ch));
	    if (ch == '.')
		getch();
	    if (!isdigit(ch))
		ungetc(ch, yyin);
	    else {
		string[i++] = '.';
		do {
		    string[i++] = ch;
		    getch();
		} while (isdigit(ch));
		if (ch == 'e' || ch == 'E') {
		    string[i++] = ch;
		    getch();
		    if (ch == '-' || ch == '+') {
			string[i++] = ch;
			getch();
		    }
		    while (isdigit(ch)) {
			string[i++] = ch;
			getch();
		    }
		}
		string[i] = '\0';
		yylval.dbl = strtod(string, NULL);
		return FLOAT_;
	    }
	    string[i] = '\0';
	    yylval.num = strtol(string, NULL, 0);
	    return INTEGER_;
	}
	ungetc(ch, yyin);
	ch = '-';
	/* ELSE '-' is not unary minus, fall through */
    default:
	do {
	    string[i++] = ch;
	    getch();
	} while (isalnum(ch) || strchr("-=_", ch));
	string[i] = '\0';
	if (strcmp(string, "true") == 0) {
	    yylval.num = 1;
	    return BOOLEAN_;
	}
	if (strcmp(string, "false") == 0) {
	    yylval.num = 0;
	    return BOOLEAN_;
	}
	yylval.str = strdup(string);
	return SYMBOL_;
    }
}

void new_buffer(void)
{
}

int old_buffer(void)
{
    return 0;
}

void setechoflag(int flag)
{
    dummy = flag;
}
