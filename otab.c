/*
    module  : otab.c
    version : 1.5
    date    : 03/05/24
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

static OpTable optable[] = {
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
 * tablesize - return the size of the table, to be used when searching from the
 *	       end of the table to the start.
 */
PUBLIC int tablesize(void)
{
    return sizeof(optable) / sizeof(optable[0]);
}

/*
    readtable - return a pointer into optable; when looping, the index i is
		increased from 0 onwards until the index becomes invalid.
*/
PUBLIC OpTable *readtable(int i)
{
    int size;

    size = tablesize();
    return i >= 0 && i < size ? &optable[i] : 0;
}
