/*
    module  : environ.h
    version : 1.5
    date    : 06/19/22
*/
typedef struct dict_t {
    char *name, *print;
    unsigned flags;
    union {
	proc_t proc;
	struct Node *body;
    };
} dict_t;

typedef int pEntry;

KHASH_MAP_INIT_STR(Symtab, pEntry)

typedef struct Env {
    vector(dict_t) *dict; /* symbol table */
    khash_t(Symtab) *hash;
    struct Node *stk;
    YYSTYPE yylval, bucket; /* used by NEWNODE defines */
    char *hide_stack[DISPLAYMAX];
    struct module {
        char *name;
        int hide;
    } module_stack[DISPLAYMAX];
    int firstlibra;
} Env;
