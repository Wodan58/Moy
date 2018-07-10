/*
    module  : builtin.c
    version : 1.3
    date    : 07/10/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "joy.h"
#include "decl.h"

#ifdef _MSC_VER
#define __func__	__FUNCTION__
#endif

void trace(const char *str);

#ifdef DEBUG
#define TRACE		if (debugging) trace(__func__)
#else
#define TRACE
#endif

#include "prims.h"

#ifdef VECTOR
Stack *theStack;
#else
#ifdef _MSC_VER
node_t *stk;
#endif

node_t memory[MEMORYMAX];
#endif

typedef struct table_t {
    proc_t proc;
    char *name;
} table_t;

extern table_t table[];

/* this file */
void joy_init(int argc, char *argv[]);
code_t *joy_code(void);
size_t joy_leng(code_t *cur);
code_t *stk2lst(void);
void lst2stk(code_t *cur);
void execute(code_t *cur);
void do_push(node_t temp);
void do_push_dbl(float dbl);
node_t do_pop(void);
int print_dbl(node_t cur);
void print_node(node_t cur);
void print_list(code_t *cur);
void trace(const char *str);
char *procname(proc_t proc);
proc_t nameproc(char *name);

/* other files */
int yylex(void);
void include(char *str);
void readfactor(int sym);
void setechoflag(int flag);

#define DOWN_64K	0xFFFF0000
#define PEPOINTER	15
#define IMAGE_BASE	13
#define BASE_OF_CODE	11
#define SIZE_OF_CODE	7
#define IMAGE_SIZE	20

#ifndef _MSC_VER
extern int _image_base__[], _section_alignment__[], etext[], _end__[];
#endif

char **g_argv;
int g_argc, debugging, autoput = 1, tracegc;
intptr_t start_of_prog, start_of_text, start_of_data, start_of_heap;

/* primitives */
#define PRIVATE
#define RUNTIME
#include "prims.c"

void joy_init(int argc, char *argv[])
{
    char *ptr;
    int rv = 0;

    setbuf(stdout, 0);
    if (argc > 1) {
	rv = 1;
	if (argv[1][0] == '-') {
	    rv = 2;
	    if (argv[1][1] == 'd')
		debugging = 1;
	}
	ptr = argv[rv];
	if (!ptr || isdigit(*ptr))
	    rv--;
	else if ((yyin = freopen(ptr, "r", stdin)) == 0) {
	    fprintf(stderr, "failed to open the file '%s'.\n", ptr);
	    exit(1);
	}
    }
/*
 * Initialize global variables.
 */
    g_argc = argc - rv;
    g_argv = &argv[rv];
/*
 * Initialise program segments.
 */
#ifdef _MSC_VER
    {
	int *ptr;
	intptr_t start;

	start = (intptr_t)main;
	start &= DOWN_64K;
	ptr = malloc(1);
	start_of_prog = (intptr_t)ptr;
	ptr = (int *)start;
	ptr += ptr[PEPOINTER] / 4;
	start_of_text = ptr[IMAGE_BASE] + ptr[BASE_OF_CODE];
	start_of_data = start_of_text + ptr[SIZE_OF_CODE];
	start_of_heap = ptr[IMAGE_BASE] + ptr[IMAGE_SIZE];
    }
#else
    start_of_prog = (intptr_t)_image_base__;
    start_of_text = (intptr_t)start_of_prog + (intptr_t)_section_alignment__;
    start_of_data = (intptr_t)etext;
    start_of_heap = (intptr_t)_end__;
#endif
#if 0
    fprintf(stderr, "prog=%X text=%X data=%X heap=%X\n", start_of_prog,
	    start_of_text, start_of_data, start_of_heap);
#endif
/*
 * Initialise stack.
 */
#ifdef VECTOR
    vec_init(theStack);
#else
    stk = memory;
#endif
}

code_t *joy_code(void)
{
    code_t *cur;

    if ((cur = malloc(sizeof(code_t))) == 0) {
	fprintf(stderr, "Out of memory\n");
	exit(0);
    }
    cur->list = cur->next = 0;
    return cur;
}

size_t joy_leng(code_t *cur)
{
    size_t leng;

    for (leng = 0; cur; cur = cur->next)
	leng++;
    return leng;
}

code_t *stk2lst(void)
{
#ifdef VECTOR
    int i, j;
#endif
    node_t *mem;
    code_t *root = 0, *cur;

#ifdef VECTOR
    for (j = vec_size(theStack), i = 0; i < j; i++) {
#else
    for (mem = memory; mem < stk; mem++) {
#endif
	if ((cur = joy_code()) == 0)
	    return 0;
#ifdef VECTOR
	mem = vec_index(theStack, i);
#endif
	cur->num = *mem;
	cur->next = root;
	root = cur;
    }
    return root;
}

#ifdef VECTOR
void lst2stk_aux(code_t *cur)
{
    node_t *node;

    if (!cur)
	vec_clear(theStack);
    else {
	lst2stk_aux(cur->next);
	node = vec_push(theStack);
	*node = cur->num;
    }
}
#endif

void lst2stk(code_t *cur)
{
    size_t leng;

    leng = joy_leng(cur);
#ifdef VECTOR
    lst2stk_aux(cur);
#else
    for (stk = memory + leng; cur; cur = cur->next)
	*--stk = cur->num;
    stk = memory + leng;
#endif
}

void execute(code_t *cur)
{
    for (; cur; cur = cur->next)
	if (cur->num > start_of_text && cur->num < start_of_data)
	    (*cur->fun)();
	else
	    do_push(cur->num);
}

/*
push :  ->  X
Puts X on top of the stack.
*/
void do_push(node_t temp)
{
#ifdef VECTOR
    node_t *node;

    node = vec_push(theStack);
    *node = temp;
#else
    *stk++ = temp;
#endif
}

void do_push_dbl(float dbl)
{
#ifdef VECTOR
    node_t *node;

    node = vec_push(theStack);
    memcpy(node, &dbl, sizeof(node_t));
#else
    memcpy(stk++, &dbl, sizeof(node_t));
#endif
}

int print_dbl(node_t cur)
{
    float dbl;
    char buf[MAXSTR];

    memcpy(&dbl, &cur, sizeof(float));
    sprintf(buf, "%f", dbl);
    if (!strcmp(buf, "0.000000") || !strncmp(buf, "nan", 3))
	return 0;
    printf("%g ", dbl);
    return 1;
}

void print_node(node_t cur)
{
    char *ptr;

    if (print_dbl(cur))
	;
    else if (abs(cur) >= 0 && abs(cur) < start_of_prog)
	printf("%d ", cur);
    else if (cur > start_of_text && cur < start_of_data) {
	if ((ptr = procname((proc_t)cur)) == 0)
	    printf("%p ", cur);
	else
	    printf("%s ", ptr);
    } else if (cur > start_of_data && cur < start_of_heap)
	printf("\"%s\" ", (char *)cur);
    else
	print_list((code_t *)cur);
}

void print_list(code_t *cur)
{
    for (printf("[ "); cur; cur = cur->next)
	print_node(cur->num);
    printf("] ");
}

void trace(const char *str)
{
#ifdef VECTOR
    int i, j;
#endif
    node_t *cur;

    if (!strncmp(str, "do_", 3))
	str += 3;
    putchar('\t');
#ifdef VECTOR
    for (j = vec_size(theStack), i = 0; i < j; i++) {
	cur = vec_index(theStack, i);
#else
    for (cur = memory; cur < stk; cur++) {
#endif
	print_node(*cur);
    }
    printf(": %s\n", str);
}

char *procname(proc_t proc)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    return table[i].name;
    return 0;
}

proc_t nameproc(char *name)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(name, table[i].name))
	    return table[i].proc;
    return 0;
}
