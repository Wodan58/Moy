/*
    module  : gc.h
    version : 1.4
    date    : 03/12/17
*/
void *GC_malloc(size_t size);
void *GC_malloc_atomic(size_t size);
void *GC_realloc(void *ptr, size_t new_size);
char *GC_strdup(const char *str);
void GC_gcollect(void);

#define malloc(x)	GC_malloc(x)
#define realloc(x,y)	GC_realloc(x,y)
#define strdup(x)	GC_strdup(x)
#define free(x)
