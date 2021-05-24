/*
    module  : dict.c
    version : 1.14
    date    : 03/22/21
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "joy.h"
#include "symbol.h"
#include "builtin.h"
#include "decl.h"

typedef struct entry_t {
    char *name, *print;
    proc_t proc;
} entry_t;

static entry_t table[] = {
#include "trans.c"
    { 0, 0 }
};

int symtabmax(pEnv env)
{
    return vec_max(env->dict);
#if 0
    return kh_n_buckets(env->hash);
#endif
}

int symtabindex(pEnv env)
{
    return vec_size(env->dict);
#if 0
    return kh_size(env->hash);
#endif
}

unsigned dict_flags(pEnv env, int index)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, index);
    return pdic->flags;
}

void dict_setflags(pEnv env, int index, unsigned flags)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, index);
    pdic->flags = flags;
}

char *dict_descr(pEnv env, int index)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, index);
    return pdic->name;
}

char *dict_name(pEnv env, int index)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, index);
    return pdic->print && isalpha(*pdic->print) ? pdic->print : pdic->name;
}

char *dict_nickname(pEnv env, int index)
{
    dict_t *pdic;
    char *name, *ptr;

    pdic = &vec_at(env->dict, index);
    name = pdic->print ? pdic->print : pdic->name;
    if ((ptr = strchr(name, '.')) != 0)
	name = ++ptr;
    return name;
}

Node *dict_body(pEnv env, int index)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, index);
    return pdic->body;
}

int dict_size(pEnv env)
{
    return vec_size(env->dict);
}

/*
 * translate function address to symbol name
 */
char *procname(proc_t proc)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    break;
    return table[i].name;
}

/*
 * translate symbol name to function address
 */
proc_t nameproc(char *name)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(name, table[i].name))
	    break;
    return table[i].proc;
}

/*
 * Init_dict initialises the dictionary with builtins.
 */
void init_dict(pEnv env)
{
    int i, rv;
    dict_t dic;
    khiter_t key;

    env->dict = 0;
    env->hash = kh_init(symtab);
    for (i = 0; table[i].name; i++) {
	dic.name = table[i].name;
	dic.print = table[i].print;
	dic.flags = IS_ORIGINAL | IS_BUILTIN;
	dic.proc = table[i].proc;
	key = kh_put(symtab, env->hash, dic.name, &rv);
	kh_value(env->hash, key) = i;
	vec_push(env->dict, dic);
    }
}

static void initialise_entry(dict_t *pdic)
{
    memset(pdic, 0, sizeof(dict_t));
    pdic->flags = IS_UNDEFINED;
}

static int is_c_identifier(char *str)
{
    if (!isalpha(*str) && *str != '_')
	return 0;
    while (*++str)
	if (!isalnum(*str) && *str != '_')
	    return 0;
    return 1;
}

static int add_word_to_dictionary(pEnv env, char *ptr)
{
    static int seq;
    int i, rv;
    dict_t dic;
    khiter_t key;
    char str[MAXSTR];

    initialise_entry(&dic);
    dic.name = GC_strdup(ptr);
    if (!is_c_identifier(ptr)) {
	sprintf(str, "%d", ++seq);
	dic.print = GC_strdup(str);
    }
    vec_push(env->dict, dic);
    i = vec_size(env->dict) - 1;
    key = kh_put(symtab, env->hash, dic.name, &rv);
    kh_value(env->hash, key) = i;
    return i;
}

/*
 * qualify adds the module to the name, when needed.
 */
static char *qualify(char *name)
{
    int hide, local, leng;
    char buf[MAXNUM], *module, *str;

    if (strchr(name, '.'))
	return name;
    module = prefix(&hide, &local);
    if (hide && local) {
	sprintf(buf, "%d", hide);
	leng = strlen(buf) + strlen(name) + 2;
	str = GC_malloc_atomic(leng);
	sprintf(str, "%s.%s", buf, name);
	name = str;
    } else if (*module) {
	leng = strlen(module) + strlen(name) + 2;
	str = GC_malloc_atomic(leng);
	sprintf(str, "%s.%s", module, name);
	name = str;
    }
    return name;
}

/*
 * Find locates a name in the hash table. First the qualified name is tried.
 * If that fails, the normal name is tried. And if that fails, -1 is returned.
 */
static int find(pEnv env, char *name)
{
    khiter_t key;
    char *str = name;

    while ((str = iterate(str)) != 0)
	if ((key = kh_get(symtab, env->hash, str)) != kh_end(env->hash))
	    return kh_value(env->hash, key);
    if ((key = kh_get(symtab, env->hash, name)) != kh_end(env->hash))
	return kh_value(env->hash, key);
    return -1;
}

static void replace(pEnv env, char *old_name, char *new_name, int index)
{
    int rv;
    khiter_t key;

    key = kh_get(symtab, env->hash, old_name);
    kh_del(symtab, env->hash, key);
    key = kh_put(symtab, env->hash, new_name, &rv);
    kh_value(env->hash, key) = index;
}

/*
 * Lookup a name in the dictionary; the return value is the index in the
 * dictionary. First search the qualified name. If not found, search the
 * normal name. If not found, add the normal name.
 */
int lookup(pEnv env, char *name)
{
    int index;

    if ((index = find(env, name)) != -1)
	return index;
    return add_word_to_dictionary(env, name);
}

/*
 * Update a dictionary entry with a definition; the definition is located after
 * == and the entry that is being defined is located before ==.
 * First the normal name is located in the dictionary, and if found that entry
 * is updated.
 */
void enteratom(pEnv env, char *name, Node *cur)
{
    char *str;
    int index;
    dict_t *pdic;

    str = qualify(name);
    if ((index = find(env, name)) == -1)
	index = lookup(env, str);
    pdic = &vec_at(env->dict, index);
    if (strcmp(pdic->name, str)) {
	replace(env, pdic->name, str, index);
	pdic->name = str;
    }
    if (pdic->flags & IS_BUILTIN) {
	fprintf(stderr, "warning: overwriting inbuilt '%s'\n", pdic->name);
	pdic->flags &= ~IS_BUILTIN;
    }
    pdic->flags |= IS_DEFINED;
    pdic->body = cur;
}

void dump(pEnv env)
{
    FILE *fp;
    int i, leng;
    dict_t *pdic;

    if ((fp = fopen("dict.txt", "w")) == 0) {
	fprintf(stderr, "Failed to write %s\n", "dict.txt");
	exit(1);
    }
    leng = vec_size(env->dict);
    for (i = 0; i < leng; i++) {
	pdic = &vec_at(env->dict, i);
	if (pdic->flags & IS_BUILTIN)
	    fprintf(fp, "%s\t%p\t%d\n", pdic->name, pdic->proc,
		    (pdic->flags & IS_USED) ? 1 : 0);
	else if (pdic->body) {
	    fprintf(fp, "%s == ", pdic->name);
	    writeterm(env, pdic->body, fp);
	    putc('\n', fp);
	} else
	    fprintf(fp, "%s ==\n", pdic->name);
    }
    fclose(fp);
}

int check_anything_was_printed(pEnv env)
{
    int i, leng;

    leng = vec_size(env->dict);
    for (i = 0; i < leng; i++)
	if (dict_flags(env, i) & IS_PRINTED)
	    return 1;
    return 0;
}

void iterate_dict_and_write_struct(pEnv env, FILE *fp)
{
    int i, leng;

    leng = vec_size(env->dict);
    for (i = 0; i < leng; i++)
	if ((dict_flags(env, i) & IS_USED) && dict_body(env, i))
	    fprintf(fp, "{ do_%s, \"%s\" },\n", dict_nickname(env, i),
		    dict_descr(env, i));
}
