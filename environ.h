/*
    module  : environ.h
    version : 1.3
    date    : 03/16/21
*/
#include "joy.h"
#include "kvec.h"
#include "khash.h"

typedef struct dict_t {
    char *name, *print;
    unsigned flags;
    union {
	proc_t proc;
	Node *body;
    };
} dict_t;

KHASH_MAP_INIT_STR(symtab, int)

typedef struct Env {
    vector(dict_t) *dict;
    khash_t(symtab) *hash;
    Node *stk;
    YYSTYPE yylval;
} Env;
