/*
    module  : joy.h
    version : 1.2
    date    : 05/06/16
*/
#ifndef PARSER
#include "parse.h"
#endif

typedef short Operator;
typedef YYSTYPE Types;

/* parse.y */
int yyparse(void);

/* symbol.c */
void HashValue(char *name);
void lookup(void);
struct Entry *enteratom(char *name, struct Node *body);
struct Entry *initmod(char *name);
void exitmod(struct Entry *sym);
struct Entry *initpriv(void);
void stoppriv(void);
void exitpriv(struct Entry *prev);
struct Node *dblnode(double dbl, struct Node *next);
struct Node *newnode(Operator op, void *ptr, struct Node *next);
void concat(struct Node *node, struct Node *next);
struct Node *copy(struct Node *node);
struct Node *reverse(struct Node *cur);
void writeln(void);
void writestack(int compile);

/* joy.c */
int Keyword(char *str);
int ChrVal(char *str);
char *StrVal(char *str);

/* initmem.c */
void initmem(void);

/* interp1.c */
PRIVATE double Compare(struct Node *first, struct Node *second, int *error);
void dup_(void);
void swapd_(void);
void cons_(void);
void concat_(void);
void step_(void);
void manual_list_(void);
void make_manual(int style);
void decode_time(struct tm *t);
void pop_(void);
void rolldown_(void);
void rollup_(void);
void rotate_(void);
void swap_(void);
void app1_(void);
void unary2_(void);

typedef struct optable_t {
    char *name;
    void (*proc)(void);
    char *messg1, *messg2;
} optable_t;

extern struct optable_t optable[];
