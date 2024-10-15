/*
 *  module  : macros.h
 *  version : 1.1
 *  date    : 10/11/24
 */
#define USR_NEWNODE(VALUE)						\
    do { Node node; node.u.ent = VALUE; node.op = USR_;			\
    vec_push(env->stck, node); } while (0)
#define ANON_FUNCT_NEWNODE(VALUE)					\
    do { Node node; node.u.proc = VALUE; node.op = ANON_FUNCT_;		\
    vec_push(env->stck, node); } while (0)
#define BOOLEAN_NEWNODE(VALUE)						\
    do { Node node; node.u.num = VALUE; node.op = BOOLEAN_;		\
    vec_push(env->stck, node); } while (0)
#define CHAR_NEWNODE(VALUE)						\
    do { Node node; node.u.num = VALUE; node.op = CHAR_;		\
    vec_push(env->stck, node); } while (0)
#define INTEGER_NEWNODE(VALUE)						\
    do { Node node; node.u.num = VALUE; node.op = INTEGER_;		\
    vec_push(env->stck, node); } while (0)
#define SET_NEWNODE(VALUE)						\
    do { Node node; node.u.set = VALUE; node.op = SET_;			\
    vec_push(env->stck, node); } while (0)
#define STRING_NEWNODE(VALUE)						\
    do { Node node; node.u.str = VALUE; node.op = STRING_;		\
    vec_push(env->stck, node); } while (0)
#define LIST_NULLNODE							\
    do { Node node; NodeList list; vec_init(list);			\
    node.u.lis = list; node.op = LIST_; vec_push(env->stck, node);	\
    } while (0)
#define LIST_NEWNODE(VALUE)						\
    do { Node node; NodeList list; vec_init(list);			\
    list->n = sizeof(VALUE) / sizeof(*VALUE); list->c = VALUE;		\
    node.u.lis = list; node.op = LIST_; vec_push(env->stck, node);	\
    } while (0)
#define FLOAT_NEWNODE(VALUE)						\
    do { Node node; node.u.dbl = VALUE; node.op = FLOAT_;		\
    vec_push(env->stck, node); } while (0)
#define FILE_NEWNODE(VALUE)						\
    do { Node node; node.u.fil = VALUE; node.op = FILE_;		\
    vec_push(env->stck, node); } while (0)
#define BIGNUM_NEWNODE(VALUE)						\
    do { Node node; node.u.str = VALUE; node.op = BIGNUM_;		\
    vec_push(env->stck, node); } while (0)

#define NULLARY(CONSTRUCTOR, VALUE)					\
    do { CONSTRUCTOR(VALUE); } while (0)
#define UNARY(CONSTRUCTOR, VALUE)					\
    do { vec_reduce(env->stck, 1); CONSTRUCTOR(VALUE); } while (0)
#define BINARY(CONSTRUCTOR, VALUE)					\
    do { vec_reduce(env->stck, 2); CONSTRUCTOR(VALUE); } while (0)

#define GNULLARY(NODE)							\
    do { vec_push(env->stck, NODE); } while (0)
#define GUNARY(NODE)							\
    do { vec_reduce(env->stck, 1); vec_push(env->stck, NODE); } while (0)
#define GBINARY(NODE)							\
    do { vec_reduce(env->stck, 2); vec_push(env->stck, NODE); } while (0)
#define GTERNARY(NODE)							\
    do { vec_reduce(env->stck, 3); vec_push(env->stck, NODE); } while (0)
