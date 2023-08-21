/*
    module  : tokl.h
    date    : 1.1
    version : 08/21/23
*/
typedef struct {
    unsigned m; /* capacity */
    unsigned n; /* valid items */
    Token *a;   /* union */
} TokList;

#define tok_init(v)	tok_init_again(&(v))

void tok_init_again(TokList **v);

void tok_push(TokList *v, Token x);

int tok_size(TokList *v);

Token tok_pop(TokList *v);

void tok_setsize(TokList *v, int i);

void tok_reverse(TokList *v);
