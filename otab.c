/*
    module  : otab.c
    version : 1.1
    date    : 09/11/23
*/
#include "globals.h"
#include "prim.h"

#ifdef NCHECK
#define PARM(n, m)
#else
#define PARM(n, m)      parm(env, n, m, __FILE__)
#endif

static OpTable optable[] = {
    /* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{OK, "__ILLEGAL",		id_,	"A",	"->",
"internal error, cannot happen - supposedly."},

{OK, "__COPIED",		id_,	"U",	"->",
"no message ever, used for gc."},

{OK, "__USR",			id_,	"U",	"->",
"user node."},

{OK, "__ANON_FUNCT",		id_,	"U",	"->",
"op for anonymous function call."},

/* LITERALS */

{OK, " truth value type",	id_,	"A",	"->  B",
"The logical type, or the type of truth values.\nIt has just two literals: true and false."},

{OK, " character type",		id_,	"A",	"->  C",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed."},

{OK, " integer type",		id_,	"A",	"->  I",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42."},

{OK, " set type",		id_,	"A",	"->  {...}",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}."},

{OK, " string type",		id_,	"A",	"->  \"...\" ",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted."},

{OK, " list type",		id_,	"A",	"->  [...]",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *]."},

{OK, " float type",		id_,	"A",	"->  F",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)."},

{OK, " file type",		id_,	"A",	"->  FILE:",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr."},

{OK, " bignum type",		id_,	"A",	"->  F",
"The type of arbitrary precision floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)."},

{OK, "__USR_PRIME",		id_,	"A",	"->",
"user node, to be pushed."},

{OK, "__ANON_PRIME",		id_,	"U",	"->",
"function call, to be pushed."},

#include "tabl.c"
};

#include "prim.c"

/*
    readtable - return a pointer into optable; when looping, the index i
		is increased from 0 onwards until the index becomes invalid.
*/
PUBLIC OpTable *readtable(int i)
{
    int size;

    size = sizeof(optable) / sizeof(optable[0]);
    return i >= 0 && i < size ? &optable[i] : 0;
}
