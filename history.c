/*
    module  : history.c
    version : 1.3
    date    : 10/23/17
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#define MAXHIST		300

typedef struct op_types {
    Operator op;
    Operator op1;
} op_types;

typedef struct op_state {
    op_types history[MAXHIST];
    unsigned hist;
} op_state;

static unsigned hist;
static op_types history[MAXHIST];
static int init_history, no_history;

void *new_history(void)
{
    op_state *save;

    save = GC_malloc_atomic(sizeof(op_state));
    memcpy(save->history, history, sizeof(history));
    save->hist = hist;
    return save;
}

void old_history(void *old)
{
    op_state *save = old;

    memcpy(history, save->history, sizeof(history));
    hist = save->hist;
}

static char *histname(Operator op)
{
    static char *datatype[] = {
	"BOOLEAN_",
	"CHAR_",
	"INTEGER_",
	"SET_",
	"STRING_",
	"LIST_",
	"FLOAT_",
	"FILE_",
	"USR_",
	"ANON_FUNCT_",
	"SYMBOL_",
    };
    if (op >= BOOLEAN_ && op <= SYMBOL_)
	return datatype[op - BOOLEAN_];
    return printname(op);
}

void prt_history(void)
{
    unsigned i, j;

    if (no_history || !hist)
	return;
    if ((j = hist) > MAXHIST)
	j = MAXHIST;
    for (i = 0; i < j; i++)
	if (history[i].op == LIST_ && history[i].op1)
	    fprintf(stderr, "LIST_(%s);", histname(history[i].op1));
	else
	    fprintf(stderr, "%s;", histname(history[i].op));
    fprintf(stderr, "\n");
}

void add_history(unsigned op)
{
    if (no_history)
	return;
    if (!init_history) {
	init_history = 1;
	atexit(prt_history);
    }
    if (hist == MAXHIST) {
	fprintf(stderr, "out of history\n");
	no_history = 1;
	return;
    }
    history[hist].op1 = 0;
    history[hist++].op = op;
}

void add_history2(unsigned op, unsigned op1)
{
    if (no_history)
	return;
    if (!init_history) {
	init_history = 1;
	atexit(prt_history);
    }
    if (hist == MAXHIST) {
	fprintf(stderr, "out of history\n");
	no_history = 1;
	return;
    }
    history[hist].op = op;
    history[hist++].op1 = op1;
}

void clr_history(void)
{
    hist = 0;
    no_history = 2;
}

void set_history(int num)
{
    if (no_history != 2)
	no_history = !num;
}

unsigned top_history(unsigned *op)
{
    if (no_history || !hist)
	return 0;
    *op = history[hist - 1].op1;
    return history[hist - 1].op;
}

unsigned sub_history(unsigned *op)
{
    if (no_history || hist < 2)
	return 0;
    *op = history[hist - 2].op1;
    return history[hist - 2].op;
}

unsigned pop_history(unsigned *op)
{
    if (no_history || !hist)
	return 0;
    *op = history[--hist].op1;
    return history[hist].op;
}

void del_history(int num)
{
    if (no_history || !hist)
	return;
    hist -= num;
}

void chg_history(unsigned op)
{
    if (no_history || !hist)
	return;
    history[hist - 1].op = op;
}

void chg_history2(unsigned op, unsigned op1)
{
    if (no_history || !hist)
	return;
    history[hist - 1].op = op;
    history[hist - 1].op1 = op1;
}

void *save_history(void *ptr, unsigned op, unsigned op1)
{
    op_state *save;

    if ((save = ptr) == 0) {
	save = GC_malloc_atomic(sizeof(op_state));
	save->hist = 0;
    }
    if (save->hist < MAXHIST) {
	save->history[save->hist].op = op;
	save->history[save->hist++].op1 = op1;
    }
    return save;
}

void swap_history(void *ptr)
{
    unsigned i, j;
    op_state *save;
    Operator op, op1;

    if ((save = ptr) == 0 || !save->hist)
	return;
    for (i = 0, j = save->hist - 1; i < j; i++, j--) {
	op = save->history[i].op;
	op1 = save->history[i].op1;
	save->history[i].op = save->history[j].op;
	save->history[i].op1 = save->history[j].op1;
	save->history[j].op = op;
	save->history[j].op1 = op1;
    }
}

int rest_history(void *ptr, unsigned *op, unsigned *op1)
{
    op_state *save;

    if ((save = ptr) == 0 || !save->hist)
	return 0;
    *op = save->history[--save->hist].op;
    *op1 = save->history[save->hist].op1;
    return 1;
}
