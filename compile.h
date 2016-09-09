/*
 *  module  : compile.h
 *  version : 1.3
 *  date    : 09/09/16
 */
/* compile.h */
#include "utstring.h"

extern int compiling, identifier;

/* print.c */
int PrintFirstList(struct Node *cur, UT_string *str);
void PrintFactor(struct Node *node, UT_string *str);
void PrintTerm(struct Node *node, UT_string *str);

/* eval.c */
char *scramble(char *str);
void compile(struct Node *node);
