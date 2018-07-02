/*
    module  : symbol.c
    version : 1.13
    date    : 07/02/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"
#include "decl.h"

static char *module;
static int hide_stack[DISPLAYMAX], hide_index, hide_count, inside_hide;

/*
 * initmod registers str as module name.
 */
void initmod(char *str)
{
    definition = 1;
    module = str;
}

void exitmod(void)
{
    definition = 0;
    module = 0;
}

/*
 * initpriv registers the current hide number.
 */
void initpriv(void)
{
    definition = 1;
    if (++hide_index >= DISPLAYMAX)
	execerror("index", "display");
    hide_stack[hide_index] = ++hide_count;
    inside_hide = 1;
}

void stoppriv(void)
{
    inside_hide = 0;
}

/*
 * exitpriv clears the defintion flag.
 */
void exitpriv(void)
{
    if (!module)
	definition = 0;
    if (hide_index)
	hide_index--;
}

/*
 * initpub sets the definition flag.
 */
void initpub(void)
{
    definition = 1;
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
