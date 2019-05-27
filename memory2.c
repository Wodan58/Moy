/*
    module  : memory2.c
    version : 1.1
    date    : 05/26/19
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gc.h"
#include "joy.h"
#include "decl.h"
#include "symbol.h"

static int memptr;
static Node memory[MEMORYMAX];

#ifdef REPORT
static double count_memory;

void report_memory()
{
    fprintf(stderr, "memory  = %.0f\n", count_memory);
}
#endif

/*
 * getnode allocates nodes from a static array, unless definition is active and
 * as long as the array is not exhausted.
 */
Node *getnode(void)
{
    Node *node;
#ifdef REPORT
    static int first;

    if (!first) {
	first = 1;
	atexit(report_memory);
    }
    count_memory++;
#endif

    if (!definition && memptr < MEMORYMAX)
	return &memory[memptr++];
    if ((node = GC_malloc(sizeof(Node))) == 0)
	execerror("memory", "allocator");
    return node;
}

/*
 * freemem releases the memory that was allocated outside definitions.
 */
void freemem(void)
{
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
