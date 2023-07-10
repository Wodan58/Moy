/*
    module  : util.c
    version : 1.1
    date    : 07/10/23
*/
#include "globals.h"

PRIVATE int EscVal(char *str)
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

PUBLIC int ChrVal(char *str)
{
    if (*str == '\\')
	return EscVal(++str);
    return *str;
}

PUBLIC char *StrVal(char *str)
{
    int i = 0;
    char *buf;

    buf = GC_strdup(str);
    while (*str != '"')
	if (*str != '\\')
	    buf[i++] = *str++;
	else {
	    buf[i++] = EscVal(++str);
	    ++str;
	    if (isdigit((int)*str))
		str += 2;
	}
    buf[i] = 0;
    return buf;
}

PUBLIC char *DelSpace(char *str)
{
    int i;

    for (i = 0; str[i]; i++)		/* find end of line */
	;
    while (--i > 0)			/* remove trailing spaces */
	if (isspace((int)str[i]))
	    str[i] = 0;
	else
	    break;
    while (isspace((int)*str))		/* skip leading spaces */
	str++;
    return str;
}
