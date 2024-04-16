/*
    module  : pvec.h
    version : 1.10
    date    : 04/11/24
*/
struct NodeList {
    unsigned m : 31,	/* capacity */
	     o :  1;	/* ownership */
    unsigned n : 30,	/* valid items */
	     r :  2;	/* arity */
    YYSTYPE *a;		/* union */
    Operator *b;	/* datatype */
};

/* ownership determines whether the vector can have new elements added */
enum owner_t {
    NOT_OWNER,
    OWNER,
};

#if 0
/* arity tells: saving and restoring stack in a condition is necessary */
enum arity_t {
    ARITY_UNKNOWN,	/* not yet calculated */
    ARITY_NOT_OK,
    ARITY_OK,
};
#endif

/* initialize vector header and set the array as not owned by the head */
static inline NodeList *pvec_init(void)
{
    NodeList *v = GC_malloc(sizeof(NodeList));
    v->m = v->n = 0;
    v->a = 0;
    v->b = 0;
    v->o = NOT_OWNER;
    v->r = ARITY_UNKNOWN;
    return v;
}

/* pvec_concat concatenates two existing vectors, and returns 1 result */
static inline NodeList *pvec_concat(NodeList *v, NodeList *w)
{
    NodeList *r = GC_malloc(sizeof(NodeList));
    r->m = r->n = v->n + w->n;
    r->a = GC_malloc(r->m * sizeof(YYSTYPE));
    r->b = GC_malloc(r->m);
    memcpy(r->a, w->a, w->n * sizeof(YYSTYPE));
    memcpy(r->b, w->b, w->n);
    memcpy(r->a + w->n, v->a, v->n * sizeof(YYSTYPE));
    memcpy(r->b + w->n, v->b, v->n);
    r->o = OWNER;
    r->r = ARITY_UNKNOWN;
    return r;
}

/* pvec_add assumes that head has been initialized before it is called */
static inline NodeList *pvec_add(NodeList *v, Node x)
{
    void *ptr;

    if (v->n == v->m) {
	v->m = v->m ? v->m << 1 : 2;
	ptr = GC_malloc(v->m * sizeof(YYSTYPE));
	if (v->n)
	    memcpy(ptr, v->a, v->n * sizeof(YYSTYPE));
	v->a = ptr;
	ptr = GC_malloc(v->m);
	if (v->n)
	    memcpy(ptr, v->b, v->n);
	v->b = ptr;
	v->o = OWNER;
    }
    v->a[v->n] = x.u;
    v->b[v->n++] = x.op;
    return v;
}

static inline int pvec_cnt(NodeList *v)
{
    return v ? v->n : 0;
}

static inline int pvec_max(NodeList *v)
{
    return v ? v->m : 0;
}

/* pvec_copy assumes that v exists and need not be created array is ok */
static inline void pvec_copy(NodeList *v, NodeList *w)
{
    if ((v->n = pvec_cnt(w)) != 0) {	/* set new number of items */
	if (v->m < v->n) {		/* new number exceeds maximum */
	    v->m = v->n;
	    v->a = GC_malloc(v->m * sizeof(YYSTYPE));
	    v->b = GC_malloc(v->m);
	    v->o = OWNER;
	    v->r = w->r;
	}
	memcpy(v->a, w->a, v->n * sizeof(YYSTYPE));
	memcpy(v->b, w->b, v->n);
    }
}

/* pvec_shallow_copy makes a copy without taking ownership of the array */
static inline void pvec_shallow_copy(NodeList *v, NodeList *w)
{
    memcpy(v, w, sizeof(NodeList));
    v->o = NOT_OWNER;
}

/* pvec_shallow_copy_take_ownership makes a copy while taking ownership */
static inline void pvec_shallow_copy_take_ownership(NodeList *v, NodeList *w)
{
    if (w->o == OWNER) {
	memcpy(v, w, sizeof(NodeList));
	w->o = NOT_OWNER;
    } else
	pvec_copy(v, w);
}

static inline Node pvec_nth(NodeList *v, int i)
{
    Node node;

    node.u = v->a[i];
    node.op = v->b[i];
    return node;
}

static inline Node pvec_lst(NodeList *v)
{
    Node node;

    node.u = v->a[v->n - 1];
    node.op = v->b[v->n - 1];
    return node;
}

static inline NodeList *pvec_upd(NodeList *v, int i, Node x)
{
    v->a[i] = x.u;
    v->b[i] = x.op;
    return v;
}

static inline NodeList *pvec_del(NodeList *v)
{
    --v->n;
    return v;
}

static inline NodeList *pvec_pop(NodeList *v, Node *node)
{
    node->u = v->a[--v->n];
    node->op = v->b[v->n];
    return v;
}

static inline NodeList *pvec_cut(NodeList *v, int s)
{
    v->n = s;
    return v;
}

static inline int pvec_getarity(NodeList *v)
{
    return v->r;
}

static inline void pvec_setarity(NodeList *v, int s)
{
    v->r = s;
}
