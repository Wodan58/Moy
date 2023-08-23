/*
    module  : list.h
    date    : 1.4
    version : 08/23/23
*/
struct NodeList {
    uint64_t m : 30, /* capacity */
             n : 30, /* valid items */
             o :  1, /* ownership */
             t :  2, /* arity */
             u :  1; /* used */
    YYSTYPE *a;      /* union */
    Operator *b;     /* datatype */
};

/* arity tells: saving and restoring stack in a condition is necessary */
enum arity_t {
    ARITY_UNKNOWN, /* not yet calculated */
    ARITY_KNOWN,
    ARITY_NOT_OK,
    ARITY_OK,
};

#define lst_init(v)	lst_init_again(&(v))

/* ownership determines whether the vector can have new elements added */
enum owner_t {
    NOT_OWNER,
    OWNER,
};

/* initialize vector header and set the array as not owned by the head */
static inline void lst_init_again(NodeList **v)
{
    *v = GC_malloc(sizeof(NodeList));
    (*v)->t = ARITY_UNKNOWN;
    (*v)->m = (*v)->n = 0;
    (*v)->a = 0;
    (*v)->b = 0;
    (*v)->o = NOT_OWNER;
    (*v)->u = 0;
}

/* lst_push assumes that v has been initialized to 0 before its called */
static inline void lst_push(NodeList *v, Node x)
{
    void *ptr;
    unsigned m;

    if (v->n == v->m) {
        m = v->m ? v->m << 1 : 1;
        ptr = GC_malloc(m * sizeof(YYSTYPE));
        memcpy(ptr, v->a, v->m * sizeof(YYSTYPE));
        v->a = ptr;
        ptr = GC_malloc(m);
        memcpy(ptr, v->b, v->m);
        v->b = ptr;
        v->m = m;
        v->o = OWNER;
    }
    v->a[v->n] = x.u;
    v->b[v->n++] = x.op;
}

static inline int lst_size(NodeList *v)
{
    return v ? v->n : 0;
}

/* lst_copy assumes that v exists and need not be created; array is ok */
static inline void lst_copy(NodeList *v, NodeList *w)
{
    if ((v->n = lst_size(w)) != 0) { /* set new number of items */
        if (v->n > v->m) { /* new number exceeds maximum */
            v->a = GC_malloc(v->n * sizeof(YYSTYPE));
            v->b = GC_malloc(v->n);
            v->t = w->t;
            v->m = v->n;
            v->o = OWNER;
        }
        memcpy(v->a, w->a, v->n * sizeof(YYSTYPE));
        memcpy(v->b, w->b, v->n);
    }
}

/* lst_shallow_copy makes a copy without taking ownership of the array */
static inline void lst_shallow_copy(NodeList *v, NodeList *w)
{
    v->m = w->m;
    v->n = w->n;
    v->t = w->t;
    v->a = w->a;
    v->b = w->b;
}

/* lst_shallow_copy_take_ownership makes a copy while taking ownership */
static inline void lst_shallow_copy_take_ownership(NodeList *v, NodeList *w)
{
    if (w->o == OWNER) {
        lst_shallow_copy(v, w);
        w->o = NOT_OWNER;
        v->o = OWNER;
    } else
        lst_copy(v, w);
}

static inline Node lst_at(NodeList *v, int i)
{
    Node node;

    node.u = v->a[i];
    node.op = v->b[i];
    return node;
}

static inline void lst_assign(NodeList *v, int i, Node x)
{
    v->a[i] = x.u;
    v->b[i] = x.op;
}

static inline Node lst_pop(NodeList *v)
{
    Node node;

    node.u = v->a[--v->n];
    node.op = v->b[v->n];
    return node;
}

static inline Node lst_back(NodeList *v)
{
    Node node;

    node.u = v->a[v->n - 1];
    node.op = v->b[v->n - 1];
    return node;
}

static inline void lst_resize(NodeList *v, int s)
{
    v->n = s;
}

static inline int lst_getarity(NodeList *v)
{
    return v->t;
}

static inline void lst_setarity(NodeList *v, int s)
{
    v->t = s;
}

static inline int lst_used(NodeList *v)
{
    return v->t;
}

static inline void lst_setused(NodeList *v)
{
    v->t = 1;
}

/* lst_reverse assumes that an extra element has been added as scratch */
static inline void lst_reverse(NodeList *v)
{
    int i, j, k = lst_size(v) - 1;

    for (i = 0, j = k - 1; i < j; i++, j--) {
        v->a[k] = v->a[i];
        v->b[k] = v->b[i];
        v->a[i] = v->a[j];
        v->b[i] = v->b[j];
        v->a[j] = v->a[k];
        v->b[j] = v->b[k];
    }
    lst_resize(v, k);
}
