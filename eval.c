/*
 *  module  : eval.c
 *  version : 1.19
 *  date    : 03/21/24
 */
#include "globals.h"

#if ALARM
static volatile sig_atomic_t time_out;

static void catch_alarm(int sig) 
{
    time_out = 1;
}

static void set_alarm(int num)
{
    static unsigned char init;

    if (!init) {
	init = 1;
	signal(SIGALRM, catch_alarm);		/* install alarm clock */
    }
    alarm(num);			/* set alarm to trigger after ALARM seconds */
}
#endif

static void trace(pEnv env, FILE *fp)
{
    writestack(env, env->stck, fp);
    if (env->debugging == 2) {
	fprintf(fp, " : ");
	writeterm(env, env->prog, fp);
    }
    fputc('\n', fp);
    fflush(fp);
}

/*
 * Execute program, as long as it is not empty.
 */
void exeterm(pEnv env, NodeList *list)
{
    Node node;
    Entry ent;

#if ALARM
    if (env->alarming)
	set_alarm(ALARM);	/* set alarm to trigger after ALARM seconds */
#endif
    env->calls++;
    prog(env, list);
    while (pvec_cnt(env->prog)) {
#if ALARM
	if (time_out) {
	    time_out = 0;
	    execerror(env->filename, "more time", "exeterm");
	}
#endif
	if (env->debugging)
	    trace(env, stdout);
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
	    env->opers++;
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
    if (env->debugging)
	trace(env, stdout);	/* final stack */
#if ALARM
    if (env->alarming)
	alarm_off(0);		/* set alarm off */
#endif
}
