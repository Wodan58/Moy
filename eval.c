/*
 *  module  : eval.c
 *  version : 1.17
 *  date    : 02/12/24
 */
#include "globals.h"

#if ALARM
static volatile sig_atomic_t time_out;

PRIVATE void catch_alarm(__attribute__((unused)) int sig) 
{
    time_out = 1;
}

PRIVATE void set_alarm(pEnv env)
{
    static unsigned char init;

    if (!env->alarming)
	return;
    if (!init) {
	init = 1;
	signal(SIGALRM, catch_alarm); /* install alarm clock */
    }
    alarm(ALARM); /* set alarm to trigger after ALARM seconds */
}

PRIVATE void alarm_off(pEnv env)
{
    if (!env->alarming)
	return;
    alarm(0); /* set alarm off */
}
#endif

#ifdef STATS
static double max_data, max_code, calls, opers, total_opers;

PRIVATE void report_stats(pEnv env)
{
    if (!env->statistics)
	return;
    fflush(stdout);
    fprintf(stderr, "%.0f data nodes in use\n", max_data);
    fprintf(stderr, "%.0f code nodes in use\n", max_code);
    fprintf(stderr, "%.0f calls to joy interpreter\n", calls);
    fprintf(stderr, "%.0f operations executed\n", total_opers);
}
#endif

#ifdef TRACING
void trace(pEnv env, FILE *fp)
{
    if (!env->debugging)
	return;
    writestack(env, env->stck, fp);
    if (env->debugging == 2) {
	fprintf(fp, " : ");
	writeterm(env, env->prog, fp);
    }
    fputc('\n', fp);
    fflush(fp);
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
    set_alarm(env);		/* set alarm to trigger after ALARM seconds */
#endif
#ifdef STATS
    if (++calls == 1)		/* install only once */
	my_atexit(report_stats);
    total_opers += opers;	/* add number of operations to total count */
    opers = 0;			/* reset operations after each program */
#endif
    prog(env, list);
    while (pvec_cnt(env->prog)) {
#if ALARM
	if (time_out) {
	    time_out = 0;
	    execerror(env->filename, "more time", "exeterm");
	}
#endif
#ifdef STATS
	if (max_data < pvec_cnt(env->stck))
	    max_data = pvec_cnt(env->stck);
	if (max_code < pvec_cnt(env->prog))
	    max_code = pvec_cnt(env->prog);
	opers++;
	if (env->operats && opers > env->operats)
	    execerror(env->filename, "more operations", "exeterm");
	if (env->maximum && pvec_cnt(env->stck) > env->maximum)
	    execerror(env->filename, "more stacknodes", "exeterm");
#endif
#ifdef TRACING
	trace(env, stdout);
#endif
	env->prog = pvec_pop(env->prog, &node);
	switch (node.op) {
	case USR_:
	    ent = vec_at(env->symtab, node.u.ent);
	    if (ent.u.body)
		prog(env, ent.u.body);
	    else if (env->undeferror)
		execerror(env->filename, "definition", ent.name);
	    break;
	case ANON_FUNCT_:
	    if (env->bytecoding || env->compiling) {
		ent = vec_at(env->symtab, node.u.ent);
		(*ent.u.proc)(env);
	    } else
		(*node.u.proc)(env);
	    break;
	case USR_PRIME_:
	    node.op = USR_;
	    goto next;
	case ANON_PRIME_:
	    node.op = ANON_FUNCT_;
	    goto next;
next:
default:
	    env->stck = pvec_add(env->stck, node);
	    break;
	}
    }
#if ALARM
    alarm_off(env); /* set alarm off */
#endif
#ifdef TRACING
    trace(env, stdout); /* final stack */
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

    for (i = tablesize() - 1; i > 0; i--) {
	tab = readtable(i);
	if (tab->proc == proc)
	    return i;
    }
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
