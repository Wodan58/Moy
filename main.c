/*
 *  module  : main.c
 *  version : 1.19
 *  date    : 09/19/23
 */
#include "globals.h"

#define ERROR_ON_USRLIB 0		/* no error */

extern FILE *yyin;			/* lexr.c */
extern unsigned char mustinclude;	/* scan.c */

static jmp_buf begin;			/* restart with empty program */

/*
    abort execution and restart reading from yyin. In the NOBDW version the
    stack is cleared as well.
*/
PUBLIC void abortexecution_(int num)
{
    longjmp(begin, num);
}

/*
    report_clock - report the amount of time spent.
*/
#ifdef STATS
PRIVATE void report_clock(pEnv env)
{
    fflush(stdout);
    fprintf(stderr, "%ld milliseconds CPU to execute\n",
	   (clock() - env->startclock) * 1000 / CLOCKS_PER_SEC);
}
#endif

/*
 *  copyright - Print all copyright notices, even historical ones.
 *
 *  The version must be set on the commandline when compiling:
 *  -DJVERSION="\"alpha\"" or whatever.
 */
#ifdef COPYRIGHT
PRIVATE void copyright(char *file)
{
    int i, j = 0;
    char str[BUFFERMAX], *ptr;

    static struct {
	char *file;
	time_t stamp;
	char *gc;
    } table[] = {
	{ "joytut.inp", 994075177, "NOBDW" },
	{ "jp-joytst.joy", 994075177, "NOBDW" },
	{ "laztst.joy", 1005579152, "BDW" },
	{ "symtst.joy", 1012575285, "BDW" },
	{ "plgtst.joy", 1012575285, "BDW" },
	{ "lsptst.joy", 1012575285, "BDW" },
	{ "mtrtst.joy", 1017847160, "BDW" },
	{ "grmtst.joy", 1017847160, "BDW" },
	{ "reptst.joy", 1047653638, "NOBDW" },
	{ "jp-reprodtst.joy", 1047653638, "NOBDW" },
	{ "flatjoy.joy", 1047653638, "NOBDW" },
	{ "modtst.joy", 1047920271, "BDW" },
	{ 0, 1056113062, "NOBDW" } };

    if (strcmp(file, "stdin")) {
	if ((ptr = strrchr(file, '/')) != 0)
	    file = ptr + 1;
	for (i = 0; table[i].file; i++) {
	    if (!strcmp(file, table[i].file)) {
		strftime(str, sizeof(str), "%H:%M:%S on %b %d %Y",
		    gmtime(&table[i].stamp));
		printf("JOY  -  compiled at %s (%s)\n", str, table[i].gc);
		j = 1;
		break;
	    }
	}
    } else {
	printf("JOY  -  compiled at %s on %s", __TIME__, __DATE__);
#ifdef JVERSION
	printf(" (%s)", JVERSION);
#endif
	putchar('\n');
	j = 1;
    }
    if (j)
	printf("Copyright 2001 by Manfred von Thun\n");
}
#endif

/*
    dump the symbol table - accessed from quit_, because env is needed;
    do this only for user defined symbols.
*/
#ifdef SYMBOLS
PRIVATE void dump_table(pEnv env)
{
    int i;
    Entry ent;

    for (i = vec_size(env->symtab) - 1; i >= 0; i--) {
	ent = vec_at(env->symtab, i);
	if (!ent.is_user)
	    printf("(%d) %s\n", i, ent.name);
	else {
	    printf("(%d) %s == ", i, ent.name);
	    writeterm(env, ent.u.body, stdout);
	    putchar('\n');
	}
    }
}
#endif

/*
    options - print help on startup options and exit: options are those that
	      cannot be set from within the language itself.
*/
PRIVATE void options(void)
{
    printf("Usage: joy [options] [filename] [parameters]\n");
    printf("options, filename, parameters can be given in any order\n");
    printf("options start with '-' and are all given together\n");
    printf("parameters start with a digit\n");
    printf("the filename parameter cannot start with '-' or a digit\n");
    printf("Options:\n");
    printf("  -h : print this help text and exit\n");
#ifdef COMPILING
    printf("  -c : compile joy source into C source\n");
#endif
#ifdef TRACING
    printf("  -d : print a trace of program execution\n");
#endif
#ifdef SYMBOLS
    printf("  -s : dump symbol table functions after execution\n");
#endif
#ifdef COPYRIGHT
    printf("  -v : do not print a copyright notice\n");
#endif
#ifdef OVERWRITE
    printf("  -w : suppress warnings: overwriting, arities\n");
#endif
#if YYDEBUG
    printf("  -y : print a trace of parser execution\n");
#endif
    exit(EXIT_SUCCESS);
}

PRIVATE int my_main(int argc, char **argv)
{
    char *ptr;
    int i, j, ch;
    unsigned char helping = 0;
#ifdef COPYRIGHT
    unsigned char verbose = 1;
#endif
#ifdef SYMBOLS
    unsigned char symdump = 0;
#endif

    Env env; /* global variables */
    memset(&env, 0, sizeof(env));
    /*
     *  Start the clock. my_atexit is called from quit_ that is called in
     *  scan.c after reading EOF on the first input file.
     */
    env.startclock = clock();
#ifdef STATS
    my_atexit(report_clock);
#endif
    lst_init(env.stck);
    lst_init(env.prog);
    vec_init(env.tokens);
    vec_init(env.symtab);
#ifdef MULTI_TASK_THREAD_JOY
    vec_init(env.context);
    vec_init(env.channel);
#endif
    /*
     *  Initialize yyin and other environmental parameters.
     */
    yyin = stdin;
    env.filename = "stdin";
    env.overwrite = INIWARNING;
    if ((ptr = strrchr(env.pathname = argv[0], '/')) != 0) {
	*ptr++ = 0;
	argv[0] = ptr;
    } else if ((ptr = strrchr(env.pathname, '\\')) != 0) {
	*ptr++ = 0;
	argv[0] = ptr;
    } else
	env.pathname = ".";
    /*
     *  First look for options. They start with -.
     */
    for (i = 1; i < argc; i++)
	if (argv[i][0] == '-') {
	    for (j = 1; argv[i][j]; j++)
		switch (argv[i][j]) {
		case 'h' : helping = 1; break;
#ifdef COMPILING
		case 'c' : env.compiling = 1; break;
#endif
#ifdef TRACING
		case 'd' : env.debugging = 1; break;
#endif
#ifdef SYMBOLS
		case 's' : symdump = 1; break;
#endif
#ifdef COPYRIGHT
		case 'v' : verbose = 0; break;
#endif
#ifdef OVERWRITE
		case 'w' : env.overwrite = 0; break;
#endif
#if YYDEBUG
		case 'y' : yydebug = 1; break;
#endif
		}
	    /*
		Overwrite the options with subsequent parameters.
	    */
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    break;
	}
    /*
     *  Look for a possible filename parameter. Filenames cannot start with -
     *  and cannot start with a digit, unless preceded by a path: e.g. './'.
     */
    for (i = 1; i < argc; i++) {
	ch = argv[i][0];
	if (!isdigit(ch)) {
	    if ((yyin = freopen(env.filename = argv[i], "r", stdin)) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n",
			env.filename);
		return 0;
	    }
	    /*
	     *  Overwrite argv[0] with the filename and shift subsequent
	     *  parameters. Also change directory to that filename.
	     */
	    if ((ptr = strrchr(argv[0] = env.filename, '/')) != 0) {
		*ptr++ = 0;
		argv[0] = env.filename = ptr;
	    }
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    break;
	}
    }
    env.g_argc = argc;
    env.g_argv = argv;
#ifdef COPYRIGHT
    if (verbose)
	copyright(env.filename);
#endif
#ifdef SYMBOLS
    if (symdump)
	my_atexit(dump_table);
#endif
    if (helping)
	options();
    env.echoflag = INIECHOFLAG;
    env.autoput = INIAUTOPUT;
    env.undeferror = INIUNDEFERROR;
    inilinebuffer(env.filename);
    inisymboltable(&env);
#ifdef COMPILING
    if (env.compiling)
	initcompile(&env);
#endif
    setjmp(begin); /* return here after error or abort */
    lst_resize(env.prog, 0);
    if (mustinclude) {
	mustinclude = include(&env, "usrlib.joy", ERROR_ON_USRLIB);
	fflush(stdout); /* flush include messages */
    }
    return yyparse(&env);
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = my_main;

    GC_INIT();
    return (*m)(argc, argv);
}
