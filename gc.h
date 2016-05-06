/*
 *  module  : gc.h
 *  version : 1.1
 *  date    : 05/06/16
 */
void *GC_strdup(char *str);
void *GC_malloc_atomic(size_t size);
void *GC_realloc(void *old_ptr, size_t new_size);
void GC_gcollect(void);
void *GC_malloc(size_t size);
void GC_init(void);

#define malloc(x)	GC_malloc(x)
#define realloc(x,y)	GC_realloc(x,y)
#define free(x)		((x)?!(x):0)
