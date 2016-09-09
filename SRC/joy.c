/*
    module  : joy.c
    version : 1.2
    date    : 09/09/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "memory.h"
#include "globals1.h"

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

    buf = strdup(str);
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
