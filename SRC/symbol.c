/*
    module  : symbol.c
    version : 1.10
    date    : 03/12/17
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#define HASHSIZE	9
#define DISPLAYMAX	10	/* nesting in HIDE & MODULE */

Entry symtab[SYMTABMAX];
unsigned symtabindex, symtabstart;

static unsigned display_enter, display_lookup;
static Entry *hashentry[HASHSIZE], *display[DISPLAYMAX];

static unsigned HashValue(char *name)
{
    unsigned hashvalue = 0;

    while (*name)
	hashvalue += *name++;
    hashvalue %= HASHSIZE;
    return hashvalue;
}

static Entry *enterglobal(char *name, unsigned hashvalue)
{
    Entry *sym;

    if (symtabindex >= SYMTABMAX)
	execerror("index", "symbols");
    sym = &symtab[symtabindex++];
    sym->name = GC_strdup(name);
    sym->u.body = 0;			/* may be assigned in definition */
    sym->flags |= IS_UNKNOWN;
    sym->next = hashentry[hashvalue];
    hashentry[hashvalue] = sym;
    return sym;
}

static int namecmp(char *name, char *table)
{
    while (*name && *table && *name == *table) {
	name++;
	table++;
    }
    return *name == *table || (*name == '.' && !*table);
}

static Entry *module(char *module, char *member, Entry *sym)
{
    Entry *fields;

    while (sym->flags & IS_MODULE) {
	fields = sym->u.member;
	while (fields && !namecmp(member, fields->name))
	    fields = fields->next;
	if ((sym = fields) == 0)
	    execerror(member, module);		/* no such field in module */
	module = member;
	member = strchr(module, '.') + 1;
    }
    return sym;
}

Entry *lookup(char *name)
{
    Entry *sym;
    unsigned i, hashvalue;
    char str[ALEN], *member;

    if ((member = strchr(name, '.')) != 0) {
	strncpy(str, name, ALEN);
	str[member++ - name] = 0;
	name = str;
    }

    for (i = display_lookup; i > 0; i--)
	for (sym = display[i]; sym; sym = sym->next)
	    if (!strcmp(name, sym->name))
		return module(name, member, sym); /* found in local table */

    hashvalue = HashValue(name);

    for (sym = hashentry[hashvalue]; sym; sym = sym->next)
	if (!strcmp(name, sym->name))
	    return module(name, member, sym);

    return enterglobal(name, hashvalue);	/* not found, enter in global */
}

static void detachatom(Entry *sym, unsigned hashvalue)
{
    Entry *cur, *prev = 0;

    for (cur = hashentry[hashvalue]; cur; prev = cur, cur = cur->next)
	if (cur == sym) {
	    if (prev)
		prev->next = cur->next;
	    else
		hashentry[hashvalue] = cur->next;
	    break;
	}
}

Entry *enteratom(Entry *sym, Node *body)
{
    char *name = sym->name;

    if (display_enter > 0) {
	if (sym->flags & IS_UNKNOWN)
	    detachatom(sym, HashValue(name));
	else {
	    if (symtabindex >= SYMTABMAX)
		execerror("index", "symbols");
	    sym = &symtab[symtabindex++];
	    sym->name = GC_strdup(name);
	    sym->u.body = 0;			/* may be assigned later */
	}
	sym->flags |= IS_LOCAL;
	sym->next = display[display_enter];
	display[display_enter] = sym;
    }
    sym->flags &= ~IS_UNKNOWN;
    sym->u.body = body;
    return sym;
}

Entry *initmod(Entry *sym)
{
    sym->flags = IS_MODULE;
    ++display_lookup;
    if (++display_enter >= DISPLAYMAX)
	execerror("index", "display");
    display[display_enter] = 0;
    return sym;
}

void exitmod(Entry *sym)
{
    if (!sym)
	return;
    sym->u.member = display[display_enter--];
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

void exitpriv(Entry *prev)
{
    if (!prev)
	--display_lookup;
    else if (prev != (Entry *)-1)
	display[display_lookup] = prev;
}

void dump(void)
{
    unsigned i;

    for (i = 0; i < symtabindex; i++)
	if (symtab[i].flags & IS_MODULE)
	    printf("%s (module)\n", symtab[i].name);
	else if (symtab[i].flags & IS_BUILTIN)
	    printf("%s (%p)\n", symtab[i].name, symtab[i].u.proc);
	else {
	    printf("%s == ", symtab[i].name);
	    writeterm(symtab[i].u.body, stdout);
	    printf("\n");
	}
}
