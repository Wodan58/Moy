/*
    module  : symbol.c
    version : 1.2
    date    : 05/06/16
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <gc.h>
#include "globals1.h"

PUBLIC void gc_(void)
{
    GC_gcollect();
}

void HashValue(char *name)
{
    hashvalue = 0;
    while (*name)
	hashvalue += *name++;
    hashvalue %= HASHSIZE;
}

static void enterglobal(char *name)
{
    if (symtabindex - symtab >= SYMTABMAX)
	execerror("index", "symbols");
    location = symtabindex++;
    location->name = GC_strdup(name);
    location->u.body = 0;	/* may be assigned in definition */
    location->is_unknown = 1;
    location->next = hashentry[hashvalue];
    hashentry[hashvalue] = location;
}

static int namecmp(char *name, char *table)
{
    while (*name && *table && *name == *table) {
	name++;
	table++;
    }
    return *name == *table || (*name == '.' && !*table);
}

static void sym_module(char *module, char *member)
{
    Entry *mod_fields;

    while (location->is_module) {
	mod_fields = location->u.module_fields;
	while (mod_fields && !namecmp(member, mod_fields->name))
	    mod_fields = mod_fields->next;
	if ((location = mod_fields) == 0)
	    execerror(member, module);	/* no such field in module */
	module = member;
	member = strchr(module, '.') + 1;
    }
}

static void sym_lookup(char *name)
{
    int i;
    char str[ALEN], *member;

    if ((member = strchr(name, '.')) != 0) {
	strncpy(str, name, ALEN);
	str[member++ - name] = 0;
	name = str;
    }

    HashValue(name);
    for (i = display_lookup; i > 0; i--)
	for (location = display[i]; location; location = location->next)
	    if (!strcmp(name, location->name)) {
		sym_module(name, member);
		return;		/* found in local table */
	    }

    for (location = hashentry[hashvalue]; location != symtab;
	 location = location->next)
	if (!strcmp(name, location->name)) {
	    sym_module(name, member);
	    return;
	}

    enterglobal(name);		/* not found, enter in global */
}

void lookup(void)
{
    sym_lookup(id);
}

static void detachatom(void)
{
    Entry *cur, *prev;

    for (prev = cur = hashentry[hashvalue]; cur != symtab;
	 prev = cur, cur = cur->next)
	if (cur == location) {
	    if (prev == cur)
		hashentry[hashvalue] = cur->next;
	    else
		prev->next = cur->next;
	    break;
	}
}

Entry *enteratom(char *name, Node * body)
{
    sym_lookup(name);
    if (display_enter > 0) {
	if (location->is_unknown)
	    detachatom();
	else {
	    if (symtabindex - symtab >= SYMTABMAX)
		execerror("index", "symbols");
	    location = symtabindex++;
	    location->name = GC_strdup(name);
	    location->u.body = 0;	/* may be assigned later */
	}
	location->is_local = 1;
	location->next = display[display_enter];
	display[display_enter] = location;
    }
    location->is_unknown = 0;
    if (location < firstlibra) {
	fprintf(stderr, "warning: overwriting inbuilt '%s'\n", name);
	enterglobal(name);
    }
    location->u.body = body;
    return location;
}

Entry *initmod(char *name)
{
    enteratom(name, 0);
    location->is_module = 1;
    ++display_lookup;
    if (++display_enter >= DISPLAYMAX)
	execerror("index", "display");
    display[display_enter] = 0;
    return location;
}

void exitmod(Entry * sym)
{
    if (!sym)
	return;
    sym->u.module_fields = display[display_enter--];
    --display_lookup;
}

Entry *initpriv(void)
{
    Entry *prev = 0;

    if (display_lookup > display_enter) {
	prev = display[display_lookup];
	if (++display_enter >= DISPLAYMAX)
	    execerror("index", "display");
    } else {
	++display_lookup;
	if (++display_enter >= DISPLAYMAX)
	    execerror("index", "display");
	display[display_enter] = 0;
    }
    return prev;
}

void stoppriv(void)
{
    --display_enter;
}

void exitpriv(Entry * prev)
{
    if (!prev)
	--display_lookup;
    else if (prev != (Entry *) - 1)
	display[display_lookup] = prev;
}

#ifdef STATS
static double nodes;

static void report_nodes(void)
{
    fprintf(stderr, "%d symbols used\n", symtabindex - firstlibra);
    fprintf(stderr, "%.0f nodes allocated\n", nodes);
}

static void count_nodes(void)
{
    if (++nodes == 1)
	atexit(report_nodes);
}
#endif

Node *dblnode(double dbl, Node *next)
{
    Node *node;

    if (inside_critical && crit_ptr > critical &&
	critical <= &critical[MEMORYMAX])
	node = --crit_ptr;
    else {
	node = GC_malloc(sizeof(Node));
#ifdef STATS
	count_nodes();
#endif
	if (!node)
	    execerror("memory", "allocator");
    }
    node->op = FLOAT_;
    node->u.dbl = dbl;
    node->next = next;
    return node;
}

Node *newnode(Operator op, void *ptr, Node *next)
{
    Node *node;

    if (inside_critical && crit_ptr > critical &&
	critical <= &critical[MEMORYMAX])
	node = --crit_ptr;
    else {
	node = GC_malloc(sizeof(Node));
#ifdef STATS
	count_nodes();
#endif
	if (!node)
	    execerror("memory", "allocator");
    }
    if ((node->op = op) != JSymbol)
	node->u.ptr = ptr;
    else {
	sym_lookup(ptr);
	if (location >= firstlibra) {
	    node->op = USR_;
	    node->u.ent = location;
	} else if (location) {
	    node->op = location - symtab;
	    node->u.proc = location->u.proc;
	}
    }
    node->next = next;
    return node;
}

void concat(Node *node, Node *next)
{
    while (node->next)
	node = node->next;
    node->next = next;
}

Node *copy(Node *node)
{
    Node *root = 0, **cur;

    for (cur = &root; node; node = node->next) {
	*cur = GC_malloc(sizeof(Node));
	**cur = *node;
	cur = &(*cur)->next;
	*cur = 0;
    }
    return root;
}

Node *reverse(Node *cur)
{
    Node *old = 0, *prev;

    while (cur) {
	prev = cur;
	cur = cur->next;
	prev->next = old;
	old = prev;
    }
    return old;
}

void writeln(void)
{
    putchar('\n');
    fflush(stdout);
}

void writestack(int compile)
{
    Entry *sym;

    if (compile) {
	if (compile == 1)
	    printf("writestack(0);\n");
	for (sym = firstlibra; sym < symtabindex; sym++)
	    if (sym->is_expanding == 1)
		sym->is_expanding = 0;
	return;
    }
    if (stk == &memory[MEMORYMAX])
	return;
    if (autoput == 2)
	writeterm(stk, stdout);
    else if (autoput == 1) {
	writefactor(stk, stdout);
	POP(stk);
    }
    writeln();
}
