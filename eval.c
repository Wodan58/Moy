/*
 *  module  : eval.c
 *  version : 1.23
 *  date    : 09/17/24
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

void trace(pEnv env, FILE *fp)
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
 * Evaluate program, as long as it is not empty.
 */
void evaluate(pEnv env, NodeList list)
{
    Node node;
    Entry ent;

#if ALARM
    if (env->alarming)
	set_alarm(ALARM);	/* set alarm to trigger after ALARM seconds */
#endif
    env->calls++;
    prog(env, list);
    while (vec_size(env->prog)) {
#if ALARM
	if (time_out) {
	    time_out = 0;
	    execerror("more time", "evaluate");
	}
#endif
	if (env->debugging)
	    trace(env, stdout);
	node = vec_pop(env->prog);
	switch (node.op) {
	case USR_:
	    ent = vec_at(env->symtab, node.u.ent);
	    if (ent.u.body)
		prog(env, ent.u.body);
	    else if (env->undeferror)
		execerror("definition", ent.name);
	    continue;
	case ANON_FUNCT_:
	    (*node.u.proc)(env);
	    env->opers++;
	    continue;
	case USR_PRIME_:
	    node.op = USR_;
	    break;
	case ANON_PRIME_:
	    node.op = ANON_FUNCT_;
	    break;
	}
	vec_push(env->stck, node);
    }
    if (env->debugging)
	trace(env, stdout);	/* final stack */
#if ALARM
    if (env->alarming)
	alarm_off(0);		/* set alarm off */
#endif
}
