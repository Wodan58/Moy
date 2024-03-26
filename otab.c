/*
    module  : otab.c
    version : 1.6
    date    : 03/21/24
*/
#include "globals.h"
#include "prim.h"	/* declarations of functions */

#ifdef NCHECK
#define PARM(n, m)
#else
#define PARM(n, m)	parm(env, n, m, __FILE__)
#endif

/*
 * Specify number of quotations that a combinator consumes.
 */
enum {
    Q0,
    Q1,
    Q2,
    Q3,
    Q4
};

static struct {
    unsigned char qcode, flags;
    char *name;
    proc_t proc;
    char *arity, *messg1, *messg2;
} optable[] = {
    /* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{Q0, OK, "__ILLEGAL",		id_,	"U",	"->",
"internal error, cannot happen - supposedly."},

{Q0, OK, "__COPIED",		id_,	"U",	"->",
"no message ever, used for gc."},

{Q0, OK, "__USR",		id_,	"U",	"->",
"user node."},

{Q0, OK, "__ANON_FUNCT",	id_,	"U",	"->",
"op for anonymous function call."},

/* LITERALS */

{Q0, OK, " truth value type",	id_,	"A",	"->  B",
"The logical type, or the type of truth values.\nIt has just two literals: true and false."},

{Q0, OK, " character type",	id_,	"A",	"->  C",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed."},

{Q0, OK, " integer type",	id_,	"A",	"->  I",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42."},

{Q0, OK, " set type",		id_,	"A",	"->  {...}",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}."},

{Q0, OK, " string type",	id_,	"A",	"->  \"...\"",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted."},

{Q0, OK, " list type",		id_,	"A",	"->  [...]",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *]."},

{Q0, OK, " float type",		id_,	"A",	"->  F",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)."},

{Q0, OK, " file type",		id_,	"A",	"->  FILE:",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr."},

{Q0, OK, " bignum type",	id_,	"A",	"->  F",
"The type of arbitrary precision floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)."},

#include "tabl.c"	/* the rest of optable */
};

#include "prim.c"	/* the primitive functions themselves */

/*
 * nickname - return the name of an operator. If the operator starts with a
 *	      character that is not part of an identifier, then the nick name
 *	      is the part of the string after the first \0.
 */
static char *nickname(int ch)
{
    char *str;

    str = optable[ch].name;
    if ((ch = *str) == '_' || isalpha(ch))
	return str;
    while (*str)
	str++;
    return str + 1;
}

/*
    showname - return the display name of a datatype, used in name.
*/
char *showname(int index)
{
    return optable[index].name;
}

/*
 * operindex returns the optable entry for an operator.
 */
int operindex(pEnv env, proc_t proc)
{
    khiter_t key;

    if ((key = kh_get(Funtab, env->prim, (int64_t)proc)) != kh_end(env->prim))
	return kh_value(env->prim, key);
    return ANON_FUNCT_; /* if not found, return the index of ANON_FUNCT_ */
}

/*
    opername - return the name of an operator, used in writefactor.
*/
char *opername(pEnv env, proc_t proc)
{
    return showname(operindex(env, proc));
}

/*
 * cmpname - return the name of an operator, used in Compare.
 */
char *cmpname(pEnv env, proc_t proc)
{
    return nickname(operindex(env, proc));
}

/*
 * operarity - return the arity of an operator, used in arity.
 */
char *operarity(int index)
{
    return optable[index].arity;
}

/*
 * tablesize - return the size of the table, to be used when searching from the
 *	       end of the table to the start.
 */
#ifdef BYTECODE
int tablesize(void)
{
    return sizeof(optable) / sizeof(optable[0]);
}

/*
 *  qcode - return the qcode value of an operator or combinator.
 */
int operqcode(int index)
{
    return optable[index].qcode;
}
#endif

/*
 * Initialise the symbol table with builtins.
 * The hash tables contain an index into the symbol table.
 */
void inisymboltable(pEnv env) /* initialise */
{
    Entry ent;
    khiter_t key;
    int i, j, rv;

    env->hash = kh_init(Symtab);
    env->prim = kh_init(Funtab);
    j = sizeof(optable) / sizeof(optable[0]);
    for (i = 0; i < j; i++) {
	ent.name = optable[i].name;
	ent.is_user = 0;
	ent.flags = optable[i].flags;
	ent.u.proc = optable[i].proc;
	if (env->ignore)
	    switch (ent.flags) {
	    case IGNORE_OK:
		ent.u.proc = id_;
		break;
	    case IGNORE_POP:
		ent.u.proc = pop_;
		break;
	    case POSTPONE:
	    case IGNORE_PUSH:
		ent.u.proc = __dump_;
		break;
	    }
	key = kh_put(Symtab, env->hash, ent.name, &rv);
	kh_value(env->hash, key) = i;
	key = kh_put(Funtab, env->prim, (int64_t)ent.u.proc, &rv);
	kh_value(env->prim, key) = i;
	vec_push(env->symtab, ent);
    }
}
