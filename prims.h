/*
    module  : prims.h
    version : 1.1
    date    : 07/05/18
*/
typedef intptr_t node_t;

typedef void (*proc_t)(void);

typedef struct code_t {
    union {
	intptr_t num;
	float dbl;
	char *str;
	proc_t fun;
	uintptr_t set;
	struct code_t *list;
    };
    struct code_t *next;
} code_t;

#ifdef _MSC_VER
extern node_t *stk;
#else
register node_t *stk asm("bl");
#endif

code_t *joy_code(void);
void do_push(node_t temp);
node_t do_pop(void);
proc_t nameproc(char *name);
