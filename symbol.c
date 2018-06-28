/*
    module  : symbol.c
    version : 1.12
    date    : 06/28/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joy.h"
#include "symbol.h"

#define DISPLAYMAX	10	/* nesting in HIDE & MODULE */
#define MAXNUM		20

static char *module;
static int hide_stack[DISPLAYMAX], hide_index, hide_count, inside_hide;

/*
 * initmod registers str as module name.
 */
void initmod(char *str)
{
    module = str;
}

void exitmod(void)
{
    module = 0;
}

/*
 * initpriv registers the current hide number.
 */
void initpriv(void)
{
    if (++hide_index >= DISPLAYMAX)
	execerror("index", "display");
    hide_stack[hide_index] = ++hide_count;
    inside_hide = 1;
}

void stoppriv(void)
{
    inside_hide = 0;
}

void exitpriv(void)
{
    if (hide_index)
	hide_index--;
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
	str = malloc(leng);
	sprintf(str, "%s.%s", buf, ptr);
	return str;
    }
    if (module && !done) {
	done = 1;
	leng = strlen(module) + strlen(ptr) + 2;
	str = malloc(leng);
	sprintf(str, "%s.%s", module, ptr);
	return str;
    }
    return 0;
}
