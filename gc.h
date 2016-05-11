/*
    module  : gc.h
    version : 1.1
    date    : 05/11/16
*/
void *GC_malloc(unsigned size);
void GC_init(void);
void GC_gcollect(void);
char *GC_strdup(char *str);
void *GC_realloc(void *ptr, unsigned size);
void *GC_malloc_atomic(unsigned size);

#define GC_NEW(x)               GC_malloc(sizeof(x))
#define GC_NEW_ATOMIC(x)        GC_malloc_atomic(sizeof(x))
#define GC_MALLOC_ATOMIC(x)     GC_malloc_atomic(x)
#define GC_REGISTER_FINALIZER(a, b, c, d, e)	\
				GC_register_finalizer(a, b, c, d, e)
#define GC_INIT			GC_init

typedef unsigned long GC_word;
typedef void *(*GC_fn_type)(void *);
typedef void (*GC_finalization_proc)(void *, void *);

void *GC_call_with_alloc_lock(GC_fn_type, void *);
void GC_register_finalizer(void *, GC_finalization_proc,
			   void *, GC_finalization_proc *, void **);
void GC_win32_free_heap(void);
