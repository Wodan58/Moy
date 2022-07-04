/*
    module  : tmpfile.c
    version : 1.4
    date    : 06/16/22
*/
#include "globals.h"

static int filenum;

static void my_rmtmp(void)
{
    int i;
    char str[MAXNUM];

    for (i = 1; i <= filenum; i++) {
	sprintf(str, "t%d", i);
	remove(str);
    }
}

FILE *my_tmpfile(void)
{
    FILE *fp;
    char str[MAXNUM];

    if (!filenum)
	atexit(my_rmtmp);
    sprintf(str, "t%d", ++filenum);
    fp = fopen(str, "w+");
    return fp;
}
