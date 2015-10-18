/*
    module  : joy.c
    version : 1.1
    date    : 10/18/15
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <gc.h>
#include "globals.h"

static char *keyword[] = {
    "LIBRA", "DEFINE", "IN", "PUBLIC", "HIDE", "PRIVATE", "END", "MODULE",
    "=="
};

static int value[] = {
    JPUBLIC, JPUBLIC, JPUBLIC, JPUBLIC, JPRIVATE, JPRIVATE, END, MODULE,
    EQUAL
};

int Keyword(char *str)
{
    int i;

    for (i = 0; i < (int) (sizeof(keyword) / sizeof(keyword[0])); i++)
	if (!strcmp(str, keyword[i]))
	    return value[i];
    return JSymbol;
}

static int EscVal(char *str)
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

int ChrVal(char *str)
{
    if (*str == '\\')
	return EscVal(++str);
    return *str;
}

char *StrVal(char *str)
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
	    if (isdigit((int) *str))
		str += 2;
	}
    buf[i] = 0;
    return buf;
}
