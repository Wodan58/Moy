/*
    module  : dict.c
    version : 1.22
    date    : 06/21/22
*/
#include "globals.h"

typedef struct entry_t {
    char *name, *print;
    proc_t proc;
} entry_t;

static entry_t table[] = {
    { "", "", 0 },
#include "trans.c"
    { 0, 0, 0 }
};

int symtabmax(pEnv env)
{
    return vec_max(env->dict);
}

int symtabindex(pEnv env)
{
    return vec_size(env->dict);
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

char *dict_descr(pEnv env, Node *node)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, node->u.num);
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

/*
    Translate name to nickname.
*/
char *dict_translate(pEnv env, const char *name)
{
    int index;
    dict_t *pdic;
    khiter_t key;

    if ((key = kh_get(Symtab, env->hash, name)) != kh_end(env->hash)) {
	index = kh_value(env->hash, key);
	pdic = &vec_at(env->dict, index);
	return pdic->print;
    }
    return "not_found";
}

Node *dict_body(pEnv env, int index)
{
    dict_t *pdic;

    pdic = &vec_at(env->dict, index);
    return pdic->body;
}

/*
    dict_size - return the current size of the dictionary.
*/
int dict_size(pEnv env)
{
    return vec_size(env->dict);
}

/*
    nameproc - translate name to function address.
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
 * procname - translate function address to symbol name.
 */
char *procname(proc_t proc)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    return table[i].name;
    return "not_found";
}

/*
 * translate function address to symbol name.
 */
char *nickname(proc_t proc)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    return table[i].print;
    return "not_found";
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
    env->hash = kh_init(Symtab);
    for (i = 0; table[i].name; i++) {
	dic.name = table[i].name;
	dic.print = table[i].print;
	dic.flags = IS_ORIGINAL | IS_BUILTIN;
	dic.proc = table[i].proc;
	key = kh_put(Symtab, env->hash, dic.name, &rv);
	kh_value(env->hash, key) = i;
	vec_push(env->dict, dic);
    }
    env->firstlibra = i;
}

/*
    initialise_entry - start a dictionary entry as an undefined name.
*/
static void initialise_entry(dict_t *pdic)
{
    memset(pdic, 0, sizeof(dict_t));
    pdic->flags = IS_UNDEFINED;
}

/*
    is_c_identifier - check whether a name can be a C identifir.
*/
static int is_c_identifier(char *str)
{
    if (!isalpha(*str) && *str != '_')
	return 0;
    while (*++str)
	if (!isalnum(*str) && *str != '_')
	    return 0;
    return 1;
}

/*
    add_word_to_dictionary - add a word to the dictionary.
*/
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
    key = kh_put(Symtab, env->hash, dic.name, &rv);
    kh_value(env->hash, key) = i;
    return i;
}

/*
 * Find locates a name in the hash table. First the qualified name is tried.
 * If that fails, the normal name is tried. And if that fails, -1 is returned.
 */
static int find(pEnv env, char *name)
{
    pEntry location;

    if ((location = qualify(env, name)) == 0)
	return -1;
    return location;
}

/*
    replace - rename a symbol table entry.
*/
static void replace(pEnv env, char *old_name, char *new_name, int index)
{
    int rv;
    khiter_t key;

    key = kh_get(Symtab, env->hash, old_name);
    kh_del(Symtab, env->hash, key);
    key = kh_put(Symtab, env->hash, new_name, &rv);
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

    str = classify(env, name);
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

/*
    dump_table - dump the symbol table to stdout.
*/
void dump_table(pEnv env)
{
    int i, leng;
    dict_t *pdic;

    leng = vec_size(env->dict);
    for (i = env->firstlibra; i < leng; i++) {
	pdic = &vec_at(env->dict, i);
	if (pdic->flags & IS_BUILTIN)
	    printf("%s\t%p\t%d\n", pdic->name, pdic->proc,
		   (pdic->flags & IS_USED) ? 1 : 0);
	else if (pdic->body) {
	    printf("%s == ", pdic->name);
	    writeterm(env, pdic->body);
	    putchar('\n');
	} else
	    printf("%s ==\n", pdic->name);
    }
    fflush(stdout);
}

/*
    iterate_dict_and_write_struct - add user defined functions to the symbol
				    table.
*/
void iterate_dict_and_write_struct(pEnv env, FILE *fp)
{
    Node node;
    int i, leng;
    char *name, *nick;

    leng = vec_size(env->dict);
    for (i = 0; i < leng; i++)
	if ((dict_flags(env, i) & IS_USED) && dict_body(env, i)) {
	    nick = dict_nickname(env, i);
	    node.u.num = i;
	    name = dict_descr(env, &node);
	    if (strcmp(nick, name))
	        fprintf(fp, "{ do_%s, \"%s\\000%s\" },\n", nick, name, nick);
	    else
	        fprintf(fp, "{ do_%s, \"%s\" },\n", nick, name);
	}
}
