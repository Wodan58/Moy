/*
    module  : joygc.h
    version : 1.7
    date    : 07/02/18
*/
#ifdef strdup
#undef strdup
#endif

#define strdup(x)	ck_strdup(x)
#define malloc(x)	ck_malloc(x)
#define calloc(x,y)	ck_calloc(x,y)
#define realloc(x,y)	ck_realloc(x,y)
#define malloc_sec(x)	ck_malloc_sec(x)
#define free(x)		ck_free(x)

char *ck_strdup(char *str);
void *ck_malloc(size_t size);
void *ck_calloc(size_t count, size_t size);
void *ck_realloc(void *ptr, size_t size);
void *ck_malloc_sec(size_t size);
void ck_free(void *ptr);
void ck_collect(void);
