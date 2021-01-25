/*
    module  : outfile.c
    version : 1.5
    date    : 01/24/21
*/
#include <stdio.h>
#include <stdlib.h>
#include "decl.h"

FILE *my_tmpfile();

static int avail[MAXOUT];
static FILE *tmpfp[MAXOUT];

void initout(void)
{
    int i;

    for (i = 0; i < MAXOUT; i++) {
	if ((tmpfp[i] = my_tmpfile()) == 0) {
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

void printout(FILE *fp)
{
    int i, ch, found;

    for (i = 0; i < MAXOUT; i++) {
	rewind(tmpfp[i]);
	found = 0;
	while ((ch = fgetc(tmpfp[i])) != EOF) {
	    fputc(ch, fp);
	    found = 1;
	}
	if (found) {
	    fclose(tmpfp[i]);
	    if ((tmpfp[i] = my_tmpfile()) == 0) {
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
