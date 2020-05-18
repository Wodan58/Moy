/*
    module  : symbol.c
    version : 1.15
    date    : 03/28/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

static char *module;
static int hide_stack[DISPLAYMAX], hide_index, hide_count, inside_hide,
	   inside_pub;

/*
 * initmod registers str as module name and sets definition to 1.
 */
void initmod(char *str)
{
    module = str;
    definition = 1;
}

/*
 * exitmod deregisters the module and sets definition to 0.
 */
void exitmod(void)
{
    if (module) {
	module = 0;
	definition = 0;
    }
}

/*
 * initpriv registers the current hide number and sets definition to 1.
 */
void initpriv(void)
{
    definition = 1;
    if (++hide_index >= DISPLAYMAX)
	execerror("index", "display");
    hide_stack[hide_index] = ++hide_count;
    inside_hide = 1;
}

/*
 * stoppriv registers the transition from private to public definitions.
 */
void stoppriv(void)
{
    inside_hide = 0;
}

/*
 * exitpriv lowers the hide_index and if 0, clears the definition flag.
 */
void exitpriv(void)
{
    if (hide_index)
	hide_index--;
    if (!hide_index && !module && !inside_pub)
	definition = 0;
}

/*
 * initpub sets the definition flag, unless already in hiding or module.
 */
void initpub(void)
{
    if (!hide_index && !module) {
	definition = 1;
	inside_pub = 1;
    }
}

/*
 * exitpub unsets the definition flag, unless still in hiding or module.
 */
void exitpub(void)
{
    if (!hide_index && !module) {
	definition = 0;
	inside_pub = 0;
    }
}

/*
 * prefix returns the information contained in this file.
 */
char *prefix(int *hide, int *local)
{
    *hide = hide_index ? hide_stack[hide_index] : 0;
    *local = inside_hide;
    return module;
}

/*
 * iterate traverses the hide stack followed by module and ends with 0.
 */
char *iterate(char *name)
{
    static int index, done;
    int leng;
    char buf[MAXNUM], *ptr, *str;

    if ((ptr = strchr(name, '.')) == 0) {
	index = hide_index;
	done = 0;
	ptr = name;
    } else
	ptr++;
    if (index) {
	sprintf(buf, "%d", hide_stack[index--]);
	leng = strlen(buf) + strlen(ptr) + 2;
	str = ck_malloc_sec(leng);
	sprintf(str, "%s.%s", buf, ptr);
	return str;
    }
    if (module && !done) {
	done = 1;
	leng = strlen(module) + strlen(ptr) + 2;
	str = ck_malloc_sec(leng);
	sprintf(str, "%s.%s", module, ptr);
	return str;
    }
    return 0;
}
