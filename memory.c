/*
    module  : memory.c
    version : 1.5
    date    : 07/05/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gc.h"
#include "joy.h"
#include "symbol.h"
#include "decl.h"

static int first, memptr1, memptr2;
static Node memory1[MEMORYMAX], memory2[MEMORYMAX];

#ifdef STATS
static double count_nodes1, cur_nodes1, max_nodes1, count_defs1, count_heap1;
static double count_nodes2, cur_nodes2, max_nodes2, count_defs2, count_heap2;

static void report(void)
{
    fprintf(stderr, "nodes1 = %.0f\n", count_nodes1);
    fprintf(stderr, "max1   = %.0f\n", max_nodes1);
    fprintf(stderr, "defs1  = %.0f\n", count_defs1);
    fprintf(stderr, "heap1  = %.0f\n", count_heap1);

    fprintf(stderr, "nodes2 = %.0f\n", count_nodes2);
    fprintf(stderr, "max2   = %.0f\n", max_nodes2);
    fprintf(stderr, "defs2  = %.0f\n", count_defs2);
    fprintf(stderr, "heap2  = %.0f\n", count_heap2);
}
#endif

/*
 * getnode allocates nodes from a static array, unless definition is active and
 * until the array is not exhausted.
 */
Node *get1node(void)
{
    Node *node;

#ifdef STATS
    if (!first) {
	first = 1;
	atexit(report);
    }
    cur_nodes1++;
    if (max_nodes1 < cur_nodes1)
	max_nodes1 = cur_nodes1;
    count_nodes1++;
#endif
    if (!definition && memptr1 < MEMORYMAX)
	return &memory1[memptr1++];
#ifdef STATS
    if (definition)
	count_defs1++;
    else
	count_heap1++;
#endif
    if ((node = GC_malloc(sizeof(Node))) == 0)
	execerror("memory", "allocator");
    return node;
}

Node *get2node(void)
{
    Node *node;

#ifdef STATS
    if (!first) {
	first = 1;
	atexit(report);
    }
    cur_nodes2++;
    if (max_nodes2 < cur_nodes2)
	max_nodes2 = cur_nodes2;
    count_nodes2++;
#endif
    if (!definition && memptr2 < MEMORYMAX)
	return &memory2[memptr2++];
#ifdef STATS
    if (definition)
	count_defs2++;
    else
	count_heap2++;
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
    cur_nodes1 = 0;
    cur_nodes2 = 0;
#endif
    memset(memory1, 0, memptr1 * sizeof(Node));
    memptr1 = 0;
    memset(memory2, 0, memptr2 * sizeof(Node));
    memptr2 = 0;
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
