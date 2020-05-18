/*
    module  : dict.c
    version : 1.12
    date    : 05/14/20
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "joy.h"
#include "symbol.h"
#include "builtin.h"
#include "kvec.h"
#include "khash.h"
#include "decl.h"

typedef struct entry_t {
    char *name, *print;
    proc_t proc;
} entry_t;

static entry_t table[] = {
#include "trans.c"
    { 0, 0 }
};

typedef struct dict_t {
    char *name, *print;
    unsigned flags;
    union {
	proc_t proc;
	Node *body;
    };
} dict_t;

typedef vector(dict_t) Dict;

static Dict *dict;

KHASH_MAP_INIT_STR(symtab, int);

static khash_t(symtab) *hash;

int symtabmax(void)
{
    return vec_max(dict);
#if 0
    return kh_n_buckets(hash);
#endif
}

int symtabindex(void)
{
    return vec_size(dict);
#if 0
    return kh_size(hash);
#endif
}

unsigned dict_flags(int index)
{
    dict_t *pdic;

    pdic = &vec_at(dict, index);
    return pdic->flags;
}

void dict_setflags(int index, unsigned flags)
{
    dict_t *pdic;

    pdic = &vec_at(dict, index);
    pdic->flags = flags;
}

char *dict_descr(int index)
{
    dict_t *pdic;

    pdic = &vec_at(dict, index);
    return pdic->name;
}

char *dict_name(int index)
{
    dict_t *pdic;

    pdic = &vec_at(dict, index);
    return pdic->print && isalpha(*pdic->print) ? pdic->print : pdic->name;
}

char *dict_nickname(int index)
{
    dict_t *pdic;
    char *name, *ptr;

    pdic = &vec_at(dict, index);
    name = pdic->print ? pdic->print : pdic->name;
    if ((ptr = strchr(name, '.')) != 0)
	name = ++ptr;
    return name;
}

Node *dict_body(int index)
{
    dict_t *pdic;

    pdic = &vec_at(dict, index);
    return pdic->body;
}

int dict_size(void)
{
    return vec_size(dict);
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
void init_dict(void)
{
    int i, rv;
    dict_t dic;
    khiter_t key;

    vec_init(dict);
    hash = kh_init(symtab);
    for (i = 0; table[i].name; i++) {
	dic.name = table[i].name;
	dic.print = table[i].print;
	dic.flags = IS_ORIGINAL | IS_BUILTIN;
	dic.proc = table[i].proc;
	vec_push(dict, dic);
	key = kh_put(symtab, hash, dic.name, &rv);
	kh_value(hash, key) = i;
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

static int add_word_to_dictionary(char *ptr)
{
    static int seq;
    int i, rv;
    dict_t dic;
    khiter_t key;
    char str[MAXSTR];

    initialise_entry(&dic);
    dic.name = ck_strdup(ptr);
    if (!is_c_identifier(ptr)) {
	sprintf(str, "%d", ++seq);
	dic.print = ck_strdup(str);
    }
    vec_push(dict, dic);
    i = vec_size(dict) - 1;
    key = kh_put(symtab, hash, dic.name, &rv);
    kh_value(hash, key) = i;
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
	str = ck_malloc_sec(leng);
	sprintf(str, "%s.%s", buf, name);
	name = str;
    } else if (module) {
	leng = strlen(module) + strlen(name) + 2;
	str = ck_malloc_sec(leng);
	sprintf(str, "%s.%s", module, name);
	name = str;
    }
    return name;
}

/*
 * Find locates a name in the hash table. First the qualified name is tried.
 * If that fails, the normal name is tried. And if that fails, -1 is returned.
 */
static int find(char *name)
{
    khiter_t key;
    char *str = name;

    while ((str = iterate(str)) != 0)
	if ((key = kh_get(symtab, hash, str)) != kh_end(hash))
	    return kh_value(hash, key);
    if ((key = kh_get(symtab, hash, name)) != kh_end(hash))
	return kh_value(hash, key);
    return -1;
}

static void replace(char *old_name, char *new_name, int index)
{
    int rv;
    khiter_t key;

    key = kh_get(symtab, hash, old_name);
    kh_del(symtab, hash, key);
    key = kh_put(symtab, hash, new_name, &rv);
    kh_value(hash, key) = index;
}

/*
 * Lookup a name in the dictionary; the return value is the index in the
 * dictionary. First search the qualified name. If not found, search the
 * normal name. If not found, add the normal name.
 */
int lookup(char *name)
{
    int index;

    if ((index = find(name)) != -1)
	return index;
    return add_word_to_dictionary(name);
}

/*
 * Update a dictionary entry with a definition; the definition is located after
 * == and the entry that is being defined is located before ==.
 * First the normal name is located in the dictionary, and if found that entry
 * is updated.
 */
void enteratom(char *name, Node *cur)
{
    char *str;
    int index;
    dict_t *pdic;

    str = qualify(name);
    if ((index = find(name)) == -1)
	index = lookup(str);
    pdic = &vec_at(dict, index);
    if (strcmp(pdic->name, str)) {
	replace(pdic->name, str, index);
	pdic->name = str;
    }
    if (pdic->flags & IS_BUILTIN) {
	fprintf(stderr, "warning: overwriting inbuilt '%s'\n", pdic->name);
	pdic->flags &= ~IS_BUILTIN;
    }
    pdic->flags |= IS_DEFINED;
    pdic->body = cur;
}

void dump(void)
{
    FILE *fp;
    int i, leng;
    dict_t *pdic;

    if ((fp = fopen("dict.txt", "w")) == 0) {
	fprintf(stderr, "Failed to write %s\n", "dict.txt");
	exit(1);
    }
    leng = vec_size(dict);
    for (i = 0; i < leng; i++) {
	pdic = &vec_at(dict, i);
	if (pdic->flags & IS_BUILTIN)
	    fprintf(fp, "%s\t%p\t%d\n", pdic->name, pdic->proc,
		    (pdic->flags & IS_USED) ? 1 : 0);
	else if (pdic->body) {
	    fprintf(fp, "%s == ", pdic->name);
	    writeterm(pdic->body, fp);
	    putc('\n', fp);
	} else
	    fprintf(fp, "%s ==\n", pdic->name);
    }
    fclose(fp);
}

int check_anything_was_printed(void)
{
    int i, leng;

    leng = vec_size(dict);
    for (i = 0; i < leng; i++)
	if (dict_flags(i) & IS_PRINTED)
	    return 1;
    return 0;
}

void iterate_dict_and_write_struct(FILE *fp)
{
    char *name;
    int i, leng;

    leng = vec_size(dict);
    for (i = 0; i < leng; i++)
	if ((dict_flags(i) & IS_USED) && dict_body(i)) {
	    fprintf(fp, "{ ");
	    if (!strcmp(name = dict_nickname(i), "pop"))
		fprintf(fp, "(proc_t)");
	    fprintf(fp, "do_%s, \"%s\" },\n", name, dict_descr(i));
	}
}
