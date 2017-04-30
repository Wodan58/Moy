/*
    module  : vector.h
    version : 1.1
    date    : 10/23/16
*/
#define vector(type)	struct { unsigned n, m; type *a; }
#define vec_init(v)	do { (v) = malloc(sizeof(*(v))); (v)->n = 0; \
			(v)->m = 1; (v)->a = malloc(sizeof(*(v)->a) * \
			(v)->m); } while (0)
#define vec_top(v)	((v)->a + (v)->n - 1)
#define vec_push(v)	(((v)->n++ == (v)->m) ? ((v)->a = realloc((v)->a, \
			sizeof(*(v)->a) * ((v)->m <<= 1))), vec_top(v) : \
			vec_top(v))
#define vec_size(v)	((v)->n)
#define vec_max(v)	((v)->m)
#define vec_index(v, i)	((v)->a + i)
#define vec_subtop(v)	((v)->a + (v)->n - 2)
#define vec_pop(v)	((v)->a + --(v)->n)
#define vec_empty(v)	(!(v)->n)
#define vec_clear(v)	((v)->n = 0)
