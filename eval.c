/*
 *  module  : eval.c
 *  version : 1.2
 *  date    : 07/11/23
 */
#include "globals.h"

#ifdef NCHECK
#define PARM(n, m)
#else
#define PARM(n, m)      parm(env, n, m, __FILE__)
#endif

#ifdef STATS
static double calls, opers;

PRIVATE void report_stats(void)
{
    fprintf(stderr, "%.0f calls to joy interpreter\n", calls);
    fprintf(stderr, "%.0f operations executed\n", opers);
}
#endif

/*
    Execute program, as long as it is not empty.
*/
PUBLIC void exeterm(pEnv env)
{
    Node node;
    Entry ent;

#ifdef STATS
    if (++calls == 1)
        atexit(report_stats);
#endif
    while (vec_size(env->prog)) {
#ifdef STATS
        ++opers;
#endif
#ifdef TRACING
        if (env->debugging) {
            writestack(env, env->stck);
            printf(" : ");
            writeterm(env, env->prog);
            putchar('\n');
            fflush(stdout);
        }
#endif
        node = vec_pop(env->prog);
        switch (node.op) {
        case USR_:
            ent = sym_at(env->symtab, node.u.ent);
            if (ent.u.body)
                prog(env, ent.u.body);
            else if (env->undeferror)
                execerror("definition", ent.name);
            break;
        case ANON_FUNCT_:
            (*node.u.proc)(env);
            break;
        case USR_PRIME_:
        case ANON_PRIME_:
            node.op += 2;
            goto next;
next:
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case SET_:
        case STRING_:
        case LIST_:
        case FLOAT_:
        case FILE_:
            vec_push(env->stck, node);
            break;
#if 0
        default:
            fprintf(stderr, "exeterm: attempting to execute bad node\n");
            break;
#endif
        }
    }
}

#include "prim.h"

static OpTable optable[] = {
    /* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{OK, "__ILLEGAL",           id_,            "A",        "->",
"internal error, cannot happen - supposedly."},

{OK, "__COPIED",            id_,            "A",        "->",
"no message ever, used for gc."},

{OK, "__USR",               id_,            "U",        "->",
"user node."},

{OK, "__ANON_FUNCT",        id_,            "U",        "->",
"op for anonymous function call."},

/* LITERALS */

{OK, " truth value type",   id_,            "A",        "->  B",
"The logical type, or the type of truth values.\nIt has just two literals: true and false."},

{OK, " character type",     id_,            "A",        "->  C",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed."},

{OK, " integer type",       id_,            "A",        "->  I",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42."},

{OK, " set type",           id_,            "A",        "->  {...}",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}."},

{OK, " string type",        id_,            "A",        "->  \"...\" ",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted."},

{OK, " list type",          id_,            "A",        "->  [...]",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *]."},

{OK, " float type",         id_,            "A",        "->  F",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)."},

{OK, " file type",          id_,            "A",        "->  FILE:",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr."},

#include "tabl.c"

{OK, 0, id_, "", "->", "->"}
};

#include "prim.c"

/*
    nickname - return the name of an operator. If the operator starts with a
               character that is not part of an identifier, then the nick name
               is the part of the string after the first \0.
*/
PUBLIC char *nickname(int o)
{
    char *str;
    int ch, size;

    size = sizeof(optable) / sizeof(optable[0]) - 1;
    if (o >= 0 && o < size) {
        str = optable[o].name;
        ch = *str;
        if (isalnum(ch) || strchr(" ()-=_", ch))
            return str;
        while (*str)
            str++;
        return str + 1;
    }
    return 0;
}

/*
    showname - return the name of an operator.
*/
PUBLIC char *showname(int o)
{
    int size;

    size = sizeof(optable) / sizeof(optable[0]) - 1;
    if (o >= 0 && o < size)
        return optable[o].name;
    return 0;
}

/*
    operindex - return the optable entry for an operator.
*/
PUBLIC int operindex(proc_t proc)
{
    int i, size;

    size = sizeof(optable) / sizeof(optable[0]) - 1;
    for (i = size - 1; i > ANON_FUNCT_; i--)
        if (optable[i].proc == proc)
            break;
    return i;
}

/*
    opername - return the name of an operator, used in Compare.
*/
PUBLIC char *opername(proc_t proc)
{
    return nickname(operindex(proc));
}

/*
    printname - return the name of an operator, used in writefactor.
*/
PUBLIC char *printname(proc_t proc)
{
    return showname(operindex(proc));
}

/*
    operarity - return the arity of an operator, used in arity.
*/
PUBLIC char *operarity(proc_t proc)
{
    return optable[operindex(proc)].arity;
}

/*
    readtable - return a pointer into optable.
*/
PUBLIC OpTable *readtable(int o)
{
    int size;

    size = sizeof(optable) / sizeof(optable[0]) - 1;
    if (o >= 0 && o < size)
        return &optable[o];
    return 0;
}
