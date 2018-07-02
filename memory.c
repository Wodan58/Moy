/*
    module  : memory.c
    version : 1.4
    date    : 07/02/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gc.h"
#include "joy.h"
#include "symbol.h"
#include "decl.h"

#if 0
#define STATS
#endif

static int memptr;
static Node memory[MEMORYMAX];

#ifdef STATS
static double count_nodes, cur_nodes, max_nodes, count_defs, count_heap;

static void report(void)
{
    fprintf(stderr, "nodes = %.0f\n", count_nodes);
    fprintf(stderr, "max   = %.0f\n", max_nodes);
    fprintf(stderr, "defs  = %.0f\n", count_defs);
    fprintf(stderr, "heap  = %.0f\n", count_heap);
}
#endif

/*
 * getnode allocates nodes from a static array, unless definition is active and
 * until the array is not exhausted.
 */
Node *getnode(void)
{
    Node *node;
#ifdef STATS
    static int first;

    if (!first) {
	first = 1;
	atexit(report);
    }
    cur_nodes++;
    count_nodes++;
#endif
    if (!definition && memptr < MEMORYMAX)
	return &memory[memptr++];
#ifdef STATS
    if (definition)
	count_defs++;
    else
	count_heap++;
#endif
    if ((node = GC_malloc(sizeof(Node))) == 0)
	execerror("memory", "allocator");
    return node;
}

/*
 * freemem releases the memory that was allocated outside definitions.
 */
void freemem(void)
{
#ifdef STATS
    if (max_nodes < cur_nodes)
	max_nodes = cur_nodes;
    cur_nodes = 0;
#endif
    memset(memory, 0, memptr * sizeof(Node));
    memptr = 0;
}

/*
 * ck_strdup checks that there is no out-of-memory condition.
 */
char *ck_strdup(char *str)
{
    char *ptr;

    if ((ptr = GC_strdup(str)) == 0)
	execerror("memory", "allocator");
    return ptr;
}

/*
 * ck_malloc checks that there is no out-of-memory condition.
 */
void *ck_malloc(size_t size)
{
    void *ptr;

    if ((ptr = GC_malloc(size)) == 0)
	execerror("memory", "allocator");
    return ptr;
}

/*
 * ck_calloc checks that there is no out-of-memory condition.
 */
void *ck_calloc(size_t count, size_t size)
{
    return ck_malloc(count * size);
}

/*
 * ck_realloc checks that there is no out-of-memory condition.
 */
void *ck_realloc(void *ptr, size_t size)
{
    if ((ptr = GC_realloc(ptr, size)) == 0)
	execerror("memory", "allocator");
    return ptr;
}

/*
 * ck_malloc_sec checks that there is no out-of-memory condition.
 */
void *ck_malloc_sec(size_t size)
{
    void *ptr;

    if ((ptr = GC_malloc_atomic(size)) == 0)
	execerror("memory", "allocator");
    return ptr;
}

/*
 * ck_free makes sure that nothing gets freed outside the allocator.
 */
void ck_free(void *ptr)
{
}

/*
 * ck_collect invokes the garbage collector.
 */
void ck_collect(void)
{
    GC_gcollect();
}
