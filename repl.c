/*
    module  : repl.c
    version : 1.12
    date    : 05/27/24
*/
#include "globals.h"

/*
 * Global identifiers are stored at location. The hash table uses a classified
 * name. The name parameter has already been allocated.
 */
static int enterglobal(pEnv env, char *name)
{
    Entry ent;
    khint_t key;
    int rv, index;

    index = vec_size(env->symtab);
    ent.name = name;
    ent.is_user = 1;
    ent.flags = env->inlining ? IMMEDIATE : OK;
    ent.u.body = 0;	/* may be assigned in definition */
    key = symtab_put(env->hash, ent.name, &rv);
    kh_val(env->hash, key) = index;
    vec_push(env->symtab, ent);
    return index;
}

/*
 * Lookup first searches ident in the local symbol tables; if not found in the
 * global symbol table; if still not found enters ident in the global table.
 */
int lookup(pEnv env, char *name)
{
    int index;

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
    if ((index = qualify(env, name)) == 0)
	/* not found, enter in global, unless it is a module-member  */
	if (strchr(name, '.') == 0)
	    index = enterglobal(env, name);
    return index;
}

/*
 * Enteratom enters a symbol in the symbol table, maybe a local symbol. This
 * local symbol is also added to the hash table, but in its classified form.
 */
void enteratom(pEnv env, char *name, NodeList *list)
{
    int index;
    Entry ent;

    /*
     * Local symbols are only added during the first read of private sections
     * and public sections of a module.
     * They should be found during the second read.
     */
    if ((index = qualify(env, name)) == 0)
	index = enterglobal(env, classify(env, name));
    ent = vec_at(env->symtab, index);
    if (!ent.is_user && env->overwrite) {
	fflush(stdout);
	fprintf(stderr, "warning: overwriting inbuilt '%s'\n", ent.name);
    }
    ent.is_user = 1;
    ent.u.body = list;
    vec_at(env->symtab, index) = ent;
}

/*
 * Allocate and fill a singleton list.
 */
NodeList *newnode(Operator op, YYSTYPE u)
{
    Node node;

    node.u = u;
    node.op = op;
    return pvec_add(pvec_init(), node);
}
