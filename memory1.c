/*
    module  : memory1.c
    version : 1.2
    date    : 05/18/19
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gc.h"
#include "joy.h"
#include "decl.h"
#include "prims.h"

#if 0
static int memptr;
static code_t memory1[MEMORYMAX];
#endif

#ifdef REPORT
static double count_memory;

void report_memory()
{
    fprintf(stderr, "memory1 = %.0f\n", count_memory);
}
#endif

code_t *joy_code(void)
{
    code_t *node;
#ifdef REPORT
    static int first;

    if (!first) {
	first = 1;
	atexit(report_memory);
    }
    count_memory++;
#endif
#if 0
    if (memptr < MEMORYMAX)
	return &memory1[memptr++];
#endif
    if ((node = GC_malloc(sizeof(code_t))) == 0)
	execerror("memory", "allocator");
    return node;
}

/*
 * freemem releases the memory that was allocated outside definitions.
 */
void freemem(void)
{
#if 0
    memset(memory1, 0, memptr * sizeof(code_t));
    memptr = 0;
#endif
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
