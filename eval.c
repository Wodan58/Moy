/*
 *  module  : eval.c
 *  version : 1.11
 *  date    : 09/14/23
 */
#include "globals.h"

#if ALARM
static volatile sig_atomic_t time_out;

PRIVATE void catch_alarm(__attribute__((unused)) int sig) 
{
    time_out = 1;
}
#endif

#ifdef STATS
static double calls, opers;

PRIVATE void report_stats(void)
{
    fflush(stdout);
    fprintf(stderr, "%.0f calls to joy interpreter\n", calls);
    fprintf(stderr, "%.0f operations executed\n", opers);
}
#endif

/*
    Execute program, as long as it is not empty.
*/
PUBLIC void exeterm(pEnv env, NodeList *list)
{
    Node node;
    Entry ent;

#if ALARM
    static int init;

    if (!init) {
	init = 1;
	signal(SIGALRM, catch_alarm); /* install alarm clock */
    }
    alarm(ALARM); /* set alarm to trigger after ALARM seconds */
#endif
#ifdef STATS
    if (++calls == 1)
	atexit(report_stats);
#endif
    lst_copy(env->prog, list);
    while (lst_size(env->prog)) {
#if ALARM
	if (time_out) {
	    time_out = 0;
	    execerror(env->filename, "more time", "exeterm");
	}
#endif
#ifdef STATS
	++opers;
#endif
#ifdef TRACING
	if (env->debugging) {
	    writestack(env, env->stck, stdout);
	    printf(" : ");
	    writeterm(env, env->prog, stdout);
	    putchar('\n');
	    fflush(stdout);
	}
#endif
	node = lst_pop(env->prog);
	switch (node.op) {
	case USR_:
	    ent = vec_at(env->symtab, node.u.ent);
	    if (ent.u.body)
		prog(env, ent.u.body);
	    else if (env->undeferror)
		execerror(env->filename, "definition", ent.name);
	    break;
	case ANON_FUNCT_:
	    (*node.u.proc)(env);
	    break;
	case USR_PRIME_:
	    node.op = USR_;
	    goto next;
	case ANON_PRIME_:
	    node.op = ANON_FUNCT_;
	    goto next;
next:
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case BIGNUM_:
	case USR_STRING_:
	    lst_push(env->stck, node);
	    break;
#if 0
	default:
	    fprintf(stderr, "exeterm: attempting to execute bad node\n");
	    break;
#endif
	}
    }
#if ALARM
    alarm(0); /* set alarm off */
#endif
}

/*
    nickname - return the name of an operator. If the operator starts with a
	       character that is not part of an identifier, then the nick name
	       is the part of the string after the first \0. The nick name
	       should be equal to the filename of the operator.
*/
PRIVATE char *nickname(int ch)
{
    char *str;
    OpTable *tab;

    tab = readtable(ch);
    str = tab->name;
    if ((ch = *str) == '_' || isalpha(ch))
	return str;
    while (*str)
	str++;
    return str + 1;
}

/*
    showname - return the display name of an operator, not the filename.
*/
PUBLIC char *showname(int i)
{
    OpTable *tab;

    tab = readtable(i);
    return tab->name;
}

/*
    operindex - return the optable entry for an operator. This requires search.
*/
PUBLIC int operindex(proc_t proc)
{
    int i;
    OpTable *tab;

    for (i = 0; (tab = readtable(i)) != 0; i++)
	if (tab->proc == proc)
	    return i;
    return ANON_FUNCT_;	/* if not found, return the index of ANON_FUNCT_ */
}

/*
    cmpname - return the name of an operator, used in Compare.
*/
PUBLIC char *cmpname(proc_t proc)
{
    return nickname(operindex(proc));
}

/*
    opername - return the name of an operator, used in writefactor.
*/
PUBLIC char *opername(proc_t proc)
{
    return showname(operindex(proc));
}

/*
    operarity - return the arity of an operator, used in arity.
*/
PUBLIC char *operarity(proc_t proc)
{
    OpTable *tab;

    tab = readtable(operindex(proc));
    return tab->arity;
}
