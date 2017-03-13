/*
    module  : outfile.c
    version : 1.1
    date    : 03/12/17
*/
#include <stdio.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#define MAXOUT		10

static int avail[MAXOUT];
static FILE *tmpfp[MAXOUT];

void initout(void)
{
    int i;

    for (i = 0; i < MAXOUT; i++) {
	if ((tmpfp[i] = tmpfile()) == 0) {
	    fprintf(stderr, "error creating outfile\n");
	    exit(1);
	}
	avail[i] = 1;
    }
}

FILE *nextfile(void)
{
    int i;

    for (i = 0; i < MAXOUT; i++)
	if (avail[i]) {
	    avail[i] = 0;
	    return tmpfp[i];
	}
    fprintf(stderr, "out of output files\n");
    exit(1);
}

void closefile(FILE *fp)
{
    int i;

    for (i = 0; i < MAXOUT; i++)
	if (tmpfp[i] == fp) {
	    avail[i] = 1;
	    return;
	}
}

void printout(void)
{
    int i, ch, found;

    for (i = 0; i < MAXOUT; i++) {
	rewind(tmpfp[i]);
	found = 0;
	while ((ch = fgetc(tmpfp[i])) != EOF) {
	    putchar(ch);
	    found = 1;
	}
	if (found) {
	    fclose(tmpfp[i]);
	    if ((tmpfp[i] = tmpfile()) == 0) {
		fprintf(stderr, "error creating tmpfile\n");
		exit(1);
	    }
	}
	avail[i] = 1;
    }
}

void closeout(void)
{
    int i;

    for (i = 0; i < MAXOUT; i++)
	fclose(tmpfp[i]);
}
