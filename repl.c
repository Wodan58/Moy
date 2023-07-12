/*
    module  : repl.c
    version : 1.2
    date    : 07/12/23
*/
#include "globals.h"

/*
 *  Initialise the symbol table with builtins. There is no need to classify
 *  builtins. The hash table contains an index into the symbol table.
 */
PUBLIC void inisymboltable(pEnv env) /* initialise */
{
    Entry ent;
    int i, rv;
    khiter_t key;
    OpTable *tab;

    env->hash = kh_init(Symtab);
    for (i = 0; (tab = readtable(i)) != 0; i++) {
        ent.flags = tab->flags;
        ent.is_user = 0;
        ent.name = tab->name;
        ent.u.proc = tab->proc;
        key = kh_put(Symtab, env->hash, ent.name, &rv);
        kh_value(env->hash, key) = i;
        sym_push(env->symtab, ent);
    }
}

/*
 *  Global identifiers are stored at location. The hash table uses a classified
 *  name. The name parameter has already been allocated.
 */
PRIVATE void enterglobal(pEnv env, char *name)
{
    int rv;
    Entry ent;
    khiter_t key;

    env->location = sym_size(env->symtab);
    ent.flags = 0;
    ent.name = name;
    ent.is_user = 1;
    ent.u.body = 0; /* may be assigned in definition */
    key = kh_put(Symtab, env->hash, ent.name, &rv);
    kh_value(env->hash, key) = env->location;
    sym_push(env->symtab, ent);
}

/*
 *  Lookup first searches ident in the local symbol tables; if not found in the
 *  global symbol table; if still not found enters ident in the global table.
 */
PUBLIC void lookup(pEnv env, char *name)
{
    /*
     * Sequential search in the local tables is replaced by a search in the
     * hash table, where each entry receives a unique key built from module +
     * name, or section number + name, separated by a full stop. The hash table
     * thus contains local symbols, but each local section has its own numeric
     * identifier. Local symbols are only accessable from their accompanying
     * public sections. In case a qualified symbol cannot be found, it is
     * entered as classified symbol in the symbol table. Global symbols are not
     * added during the first time read of private sections.
     */
    if ((env->location = qualify(env, name)) == 0)
        /* not found, enter in global, unless it is a module-member  */
        if (strchr(name, '.') == 0)
            enterglobal(env, name);
}

/*
 *  Enteratom enters a symbol in the symbol table, maybe a local symbol. This
 *  local symbol is also added to the hash table, but in its classified form.
 */
PUBLIC void enteratom(pEnv env, char *name, NodeList *list)
{
    Entry *temp;

    /*
     *  Local symbols are only added during the first read of private sections
     *  and public sections of a module.
     *  They should be found during the second read.
     */
    if ((env->location = qualify(env, name)) == 0)
        enterglobal(env, classify(env, name));
    temp = sym_lvalue(env->symtab, env->location);
    if (!temp->is_user) {
        if (env->overwrite) {
            fflush(stdout);
            fprintf(stderr, "warning: overwriting inbuilt '%s'\n", temp->name);
        }
        enterglobal(env, name);
        temp = sym_lvalue(env->symtab, env->location);
    }
    temp->u.body = list;
}

/*
 *  Execute a program and print the result according to the autoput settings,
 *  if there is anything to be printed.
 */
PUBLIC void execute(pEnv env, NodeList *list)
{
    Node node;

    vec_copy(env->prog, list);
    exeterm(env);
    if (vec_size(env->stck)) {
        if (env->autoput == 2)
            writeterm(env, env->stck);
        else if (env->autoput == 1) {
            node = vec_pop(env->stck);
            if (node.op == LIST_) {
                putchar('[');
                writeterm(env, node.u.lis);
                putchar(']');
            } else
                writefactor(env, node);
        }
        putchar('\n');
    }
}

/*
 *  Allocate and fill a singleton list.
 */
PUBLIC NodeList *newnode(Operator op, YYSTYPE u)
{
    Node node;
    NodeList *list;

    vec_init(list);
    node.u = u;
    node.op = op;
    vec_push(list, node);
    return list;
}

/*
 *  Reverse a list after reading.
 */
PUBLIC void reverse(NodeList *list)
{
    Node node;

    if (list) {
        node.u.lis = 0;
        node.op = LIST_;
        vec_push(list, node); /* scratch value */
        vec_reverse(list); /* excludes scratch */
    }
}
