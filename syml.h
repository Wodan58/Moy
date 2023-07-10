/*
    module  : syml.h
    date    : 1.1
    version : 07/10/23
*/
typedef struct {
    unsigned m; /* capacity */
    unsigned n; /* valid items */
    Entry *a;   /* union */
} SymList;

#define sym_init(v)	sym_init_again(&(v))

void sym_init_again(SymList **v);

void sym_push(SymList *v, Entry x);

Entry sym_at(SymList *v, int i);

Entry *sym_lvalue(SymList *v, int i);

int sym_size(SymList *v);

int sym_max(SymList *v);
