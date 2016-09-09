/*
    module  : memory.h
    version : 1.3
    date    : 09/09/16
*/
void *GC_malloc(size_t size);
void *GC_realloc(void *ptr, size_t new_size);
char *GC_strdup(const char *str);
void GC_gcollect(void);

#define malloc(x)	GC_malloc(x)
#define realloc(x,y)	GC_realloc(x,y)
#define strdup(x)	GC_strdup(x)
#define free(x)
