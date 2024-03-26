/*
    module  : util.c
    version : 1.3
    date    : 03/21/24
*/
#include "globals.h"

int EscVal(char *str)
{
    int i, num;

    if (strchr("\"'\\btnvfr", *str)) {
	switch (*str) {
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
	    return *str;
	}
    }
    for (num = i = 0; i < 3; i++)
	num = num * 10 + *str++ - '0';
    return num;
}

/*
 * chr(0) is not allowed
 */
int ChrVal(pEnv env, char *str)
{
    int ch;

    if (*str == '\\')
	ch = EscVal(++str);
    else
        ch = *str;
    if (!ch)
	yyerror(env, "chr(0) in character constant is not supported");
    return ch;
}

/*
 * chr(0) and chr(1) are not allowed
 */
char *StrVal(pEnv env, char *str)
{
    int ch, i = 0;

    char *buf;
    buf = GC_strdup(str);
    while (*str != '"') {
	if (*str != '\\')
	    buf[i++] = ch = *str++;
	else {
	    buf[i++] = ch = EscVal(++str);
	    ++str;
	    if (isdigit((int)*str))
		str += 2;
	}
	if (ch == 0)
	    yyerror(env, "chr(0) in string constant is not supported");
	if (ch == 1)
	    yyerror(env, "chr(1) in string constant is not supported");
    }
    buf[i] = 0;
    return buf;
}
