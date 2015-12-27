/*
    module  : symbol.c
    version : 1.2
    date    : 12/27/15
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gc.h>
#include "globals1.h"

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

static char *splitname(char *name)
{
    char *ptr;

    if ((ptr = strchr(name, '.')) != 0)
	ptr++;
    return ptr;
}

static int namecmp(char *name, char *table)
{
    while (*name && *table && *name == *table) {
	name++;
	table++;
    }
    return *name == *table || (*name == '.' && *table == 0);
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
	if ((module = member) == 0)
	    return;
	member = splitname(module);
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
	printf("warning: overwriting inbuilt '%s'\n", name);
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

Node *newnode(Operator op, YYSTYPE u, Node * next)
{
    Node *node;

    if (inside_critical && crit_ptr > critical &&
			   critical <= &critical[MEMORYMAX])
	node = --crit_ptr;
    else {
	node = GC_malloc(sizeof(Node));
	if (!node)
	    execerror("memory", "allocator");
    }
    if ((node->op = op) != JSymbol)
	node->u = u;
    else {
	sym_lookup(u.str);
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

Node *reverse(Node * cur)
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

void writestack(void)
{
    if (autoput == 2 && stk) {
	writeterm(stk, stdout);
	printf("\n");
    } else if (autoput == 1 && stk) {
	writefactor(stk, stdout);
	printf("\n");
	stk = stk->next;
    }
}

void writeln(void)
{
    printf("\n");
    fflush(stdout);
}
