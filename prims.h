/*
    module  : prims.h
    version : 1.3
    date    : 12/30/18
*/
typedef intptr_t node_t;

typedef void (*proc_t)(void);

typedef struct code_t {
    union {
	intptr_t num;
	float dbl;
	char *str;
	proc_t fun;
	intptr_t set;
	struct code_t *list;
    };
    struct code_t *next;
} code_t;

#ifdef VECTOR
#include "vector.h"

typedef vector(node_t) Stack;

extern Stack *theStack;

#define stk	vec_index(theStack, vec_size(theStack))
#else
#ifdef _MSC_VER
extern node_t *stk;
#else
register node_t *stk asm("bl");
#endif
#endif

code_t *joy_code(void);
void do_push(node_t temp);
node_t do_pop(void);
proc_t nameproc(char *name);
