/*
    module  : memory1.c
    version : 1.1
    date    : 07/05/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gc.h"

void execerror(char *message, const char *op);

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
