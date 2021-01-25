/*
    module  : tmpfile.c
    version : 1.2
    date    : 01/25/21
*/
#include <stdio.h>
#include <stdlib.h>
#include "decl.h"

static int filenum;

static void my_rmtmp(void)
{
    int i, j = 0;
    char str[MAXNUM];

    for (i = 1; i <= filenum; i++) {
	sprintf(str, "t%d", i);
	if (remove(str))
	    j++;
    }
    if (j)
	fprintf(stderr, "removing %d temporary files failed\n", j);
}

FILE *my_tmpfile(void)
{
    char str[MAXNUM];

    if (!filenum)
	atexit(my_rmtmp);
    sprintf(str, "t%d", ++filenum);
    return fopen(str, "w+");
}
