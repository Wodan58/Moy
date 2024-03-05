/*
 *  module  : main.c
 *  version : 1.31
 *  date    : 03/05/24
 */
#include "globals.h"

extern FILE *yyin;			/* lexr.c */

static jmp_buf begin;			/* restart with empty program */

char *bottom_of_stack;			/* used in gc.c */

/*
    abort execution and restart reading from yyin. In the NOBDW version the
    stack is cleared as well.
*/
PUBLIC void abortexecution_(int num)
{
    fflush(yyin);
    longjmp(begin, num);
}

/*
    report_clock - report the amount of time spent.
*/
#ifdef STATS
PRIVATE void report_clock(pEnv env)
{
    if (!env->statistics)
	return;
    fflush(stdout);
    fprintf(stderr, "%.0f garbage collections\n", (double)GC_get_gc_no());
    fprintf(stderr, "%ld milliseconds CPU to execute\n",
	   (clock() - env->startclock) * 1000 / CLOCKS_PER_SEC);
}
#endif

/*
 *  copyright - Print all copyright notices, even historical ones.
 *
 *  The version must be set on the commandline when compiling:
 *  -DVERS="\"alpha\"" or whatever.
 */
#ifdef COPYRIGHT
PRIVATE void copyright(char *file)
{
    int i, j = 0;
    char str[BUFFERMAX];

    static struct {
	char *file;
	time_t stamp;
	char *gc;
    } table[] = {
	{ "tutinp", 994075177, "NOBDW" },
	{ "jp-joytst", 994075177, "NOBDW" },
	{ "laztst", 1005579152, "BDW" },
	{ "symtst", 1012575285, "BDW" },
	{ "plgtst", 1012575285, "BDW" },
	{ "lsptst", 1012575285, "BDW" },
	{ "mtrtst", 1017847160, "BDW" },
	{ "grmtst", 1017847160, "BDW" },
	{ "reptst", 1047653638, "NOBDW" },
	{ "jp-reprodtst", 1047653638, "NOBDW" },
	{ "flatjoy", 1047653638, "NOBDW" },
	{ "modtst", 1047920271, "BDW" },
	{ 0, 1056113062, "NOBDW" } };

    if (strcmp(file, "stdin")) {
	for (i = 0; table[i].file; i++) {
	    if (!strncmp(file, table[i].file, strlen(table[i].file))) {
		strftime(str, sizeof(str), "%H:%M:%S on %b %d %Y",
			 gmtime(&table[i].stamp));
		printf("JOY  -  compiled at %s (%s)\n", str, table[i].gc);
		j = 1;
		break;
	    }
	}
    } else {
	printf("JOY  -  compiled at %s on %s", __TIME__, __DATE__);
#ifdef VERS
	printf(" (%s)", VERS);
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
PRIVATE void options(pEnv env)
{
    char str[BUFFERMAX];

    printf("Usage: joy (options | filenames | parameters)*\n");
    printf("options, filenames, parameters can be given in any order\n");
    printf("options start with '-' and parameters start with a digit\n");
    printf("filenames can be preceded by a pathname: e.g. './'\n");
    printf("Features included (+) or not (-):\n");
    sprintf(str, " symbols  copyright  jversion  tracing  stats  ncheck");
#ifdef SYMBOLS
    str[0] = '+';
#else
    str[0] = '-';
#endif
#ifdef COPYRIGHT
    str[9] = '+';
#else
    str[9] = '-';
#endif
#ifdef VERS
    str[20] = '+';
#else
    str[20] = '-';
#endif
#ifdef TRACING
    str[30] = '+';
#else
    str[30] = '-';
#endif
#ifdef STATS
    str[39] = '+';
#else
    str[39] = '-';
#endif
#ifdef NCHECK
    str[46] = '+';
#else
    str[46] = '-';
#endif
    printf("%s\n", str);
    sprintf(str, " tokens  ndebug  settings  yydebug  overwrite  arity");
#ifdef TOKENS
    str[0] = '+';
#else
    str[0] = '-';
#endif
#ifdef NDEBUG
    str[8] = '+';
#else
    str[8] = '-';
#endif
#ifdef SETTINGS
    str[16] = '+';
#else
    str[16] = '-';
#endif
#if YYDEBUG
    str[26] = '+';
#else
    str[26] = '-';
#endif
#ifdef OVERWRITE
    str[35] = '+';
#else
    str[35] = '-';
#endif
#ifdef ARITY
    str[46] = '+';
#else
    str[46] = '-';
#endif
    printf("%s\n", str);
    sprintf(str, " alarm  multitask  bignums  compiler  bytecodes");
#if ALARM
    str[0] = '+';
#else
    str[0] = '-';
#endif
#ifdef USE_MULTI_THREADS_JOY
    str[7] = '+';
#else
    str[7] = '-';
#endif
#ifdef USE_BIGNUM_ARITHMETIC
    str[18] = '+';
#else
    str[18] = '-';
#endif
#ifdef COMPILER
    str[27] = '+';
#else
    str[27] = '-';
#endif
#ifdef BYTECODE
    str[37] = '+';
#else
    str[37] = '-';
#endif
    printf("%s\n", str);
#ifdef COMP
    printf("Compile flags: %s\n", COMP);
#endif
#ifdef LINK
    printf("Linker flags: %s\n", LINK);
#endif
    printf("Options:\n");
#ifdef SETTINGS
    printf("  -a : set the autoput flag (0-2)\n");
#endif
#ifdef BYTECODE
    printf("  -b : compile a joy program to bytecode\n");
#endif
#ifdef COMPILER
    printf("  -c : compile joy source into C source\n");
#endif
#ifdef TRACING
    printf("  -d : print a trace of stack development\n");
#endif
#ifdef SETTINGS
    printf("  -e : set the echoflag (0-3)\n");
#endif
#ifdef BYTECODE
    printf("  -f : display a byte code file and exit\n");
#endif
#ifdef SETTINGS
    printf("  -g : set the __tracegc flag (0-6)\n");
#endif
    printf("  -h : print this help text and exit\n");
#ifdef SETTINGS
    printf("  -i : ignore impure functions\n");
#endif
#if defined(BYTECODE) || defined(COMPILER)
    printf("  -j : filename parameter is a .joy file\n");
#endif
#ifdef KEYBOARD
    printf("  -k : allow keyboard input in raw mode\n");
#endif
#ifdef SETTINGS
    printf("  -l : do not read usrlib.joy at startup\n");
#endif
#ifdef STATS
    printf("  -m : set maximum limit of data stack\n");
    printf("  -n : limit the number of operations\n");
#endif
#if defined(BYTECODE) || defined(COMPILER)
    printf("  -o : name of output file/function\n");
#endif
#ifdef TOKENS
    printf("  -p : print debug list of tokens\n");
#endif
#ifdef SETTINGS
    printf("  -q : operate in quiet mode\n");
#endif
#ifdef WRITE_USING_RECURSION
    printf("  -r : print without using recursion\n");
#endif
#ifdef SYMBOLS
    printf("  -s : dump symbol table after execution\n");
#endif
#ifdef TRACING
    printf("  -t : print a trace of program execution\n");
#endif
#ifdef SETTINGS
    printf("  -u : set the undeferror flag (0,1)\n");
#endif
#ifdef COPYRIGHT
    printf("  -v : do not print a copyright notice\n");
#endif
#ifdef OVERWRITE
    printf("  -w : suppress warnings: overwriting, arities\n");
#endif
#ifdef STATS
    printf("  -x : print statistics after program finishes\n");
#endif
#if YYDEBUG
    printf("  -y : print a trace of parser execution\n");
#endif
#if ALARM
    printf("  -z : time out after %d seconds\n", ALARM);
#endif
    quit_(env);
}

PRIVATE void unknown_opt(pEnv env, char *exe, int ch)
{
    printf("Unknown option argument: \"-%c\"\n", ch);
    printf("More info with: \"%s -h\"\n", exe);
    quit_(env);
}

PRIVATE int my_main(int argc, char **argv)
{
/*
 * These variables need to be static because of an intervening longjmp.
 */
    static unsigned char mustinclude = 1, joy = 0;
#ifdef BYTECODE
    static unsigned char skip = 6;
#endif

    int i, j, ch;
    char *ptr, *exe;		/* joy binary */
/*
 * A number of flags can be handled within the main function; no need to pass
 * them to subordinate functions.
 */
    unsigned char helping = 0, unknown = 0;
#ifdef COPYRIGHT
    unsigned char verbose = 1;
#endif
#ifdef SYMBOLS
    unsigned char symdump = 0;
#endif
#ifdef BYTECODE
    unsigned char listing = 0;
    char *filename = "a.out";	/* filename when rewriting */
#endif
#ifdef KEYBOARD
    unsigned char raw = 0;
#endif

    Env env;	/* global variables */
    memset(&env, 0, sizeof(env));
    /*
     *  Start the clock. my_atexit is called from quit_ that is called in
     *  scan.c after reading EOF on the first input file.
     */
    env.startclock = clock();
#ifdef STATS
    my_atexit(report_clock);
#endif
    vec_init(env.tokens);
    vec_init(env.symtab);
#ifdef USE_MULTI_THREADS_JOY
    vec_init(env.context);
    vec_init(env.channel);
#endif
    /*
     *  Initialize yyin and other environmental parameters.
     */
    yyin = stdin;
    env.filename = "stdin";
    env.autoput = INIAUTOPUT;
    env.echoflag = INIECHOFLAG;
    env.undeferror = INIUNDEFERROR;
    env.overwrite = INIWARNING;
    /*
     * Extract the pathname from the program that started this.
     */
    if ((ptr = strrchr(env.pathname = exe = argv[0], '/')) != 0) {
	*ptr++ = 0;
	argv[0] = exe = ptr;
    } else if ((ptr = strrchr(env.pathname, '\\')) != 0) {
	*ptr++ = 0;
	argv[0] = exe = ptr;
    } else
	env.pathname = ".";

    /*
     *  First look for options. They start with -.
     */
    for (i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
	    for (j = 1; argv[i][j]; j++) {
		switch (argv[i][j]) {
#ifdef SETTINGS
		case 'a' : ptr = &argv[i][j + 1];
			   if (!env.autoput_set)
				env.autoput = atoi(ptr);/* numeric payload */
			   env.autoput_set = 1;
			   ch = *ptr;			/* first digit */
			   while (isdigit(ch)) {
			       j++;			/* point last digit */
			       ptr++;
			       ch = *ptr;
			   }
			   break;
#endif
#ifdef BYTECODE
		case 'b' : env.bytecoding = 2; break;	/* prepare & suspend */
#endif
#ifdef COMPILER
		case 'c' : env.compiling = 2; break;	/* prepare & suspend */
#endif
#ifdef TRACING
		case 'd' : env.debugging = 1; break;
#endif
#ifdef SETTINGS
		case 'e' : ptr = &argv[i][j + 1];
			   env.echoflag = atoi(ptr);	/* numeric payload */
			   env.echoflag_set = 1;
			   ch = *ptr;			/* first digit */
			   while (isdigit(ch)) {
			       j++;			/* point last digit */
			       ptr++;
			       ch = *ptr;
			   }
			   break;
#endif
#ifdef BYTECODE
		case 'f' : listing = 1; break;
#endif
#ifdef SETTINGS
		case 'g' : ptr = &argv[i][j + 1];
			   env.tracegc = atoi(ptr);	/* numeric payload */
			   ch = *ptr;			/* first digit */
			   while (isdigit(ch)) {
			       j++;			/* point last digit */
			       ptr++;
			       ch = *ptr;
			   }
			   break;
#endif
		case 'h' : helping = 1; break;
#ifdef SETTINGS
		case 'i' : env.ignore = 1; break;
#endif
#if defined(BYTECODE) || defined(COMPILER)
		case 'j' : joy = 1; break;		/* enforce .joy */
#endif
#ifdef KEYBOARD
		case 'k' : raw = 1; env.autoput = 0;	/* terminal raw mode */
			   env.autoput_set = 1;		/* prevent override */
			   break;			/* & disable autoput */
#endif
#ifdef SETTINGS
		case 'l' : mustinclude = 0; break;	/* include usrlib.joy */
#endif
#ifdef STATS
		case 'm' : ptr = &argv[i][j + 1];
			   env.maximum = atoi(ptr);	/* numeric payload */
			   ch = *ptr;			/* first digit */
			   while (isdigit(ch)) {
			       j++;			/* point last digit */
			       ptr++;
			       ch = *ptr;
			   }
			   break;
		case 'n' : ptr = &argv[i][j + 1];
			   env.operats = atoi(ptr);	/* numeric payload */
			   ch = *ptr;			/* first digit */
			   while (isdigit(ch)) {
			       j++;			/* point last digit */
			       ptr++;
			       ch = *ptr;
			   }
			   break;
#endif
#if defined(BYTECODE) || defined(COMPILER)
		case 'o' : filename = &argv[i][j + 1];	/* string payload */
			   goto next_parm;
#endif
#ifdef TOKENS
		case 'p' : env.printing = 1; break;
#endif
#ifdef SETTINGS
		case 'q' : env.quiet = 1; break;
#endif
#ifdef WRITE_USING_RECURSION
		case 'r' : env.recurse = 1; break;
#endif
#ifdef SYMBOLS
		case 's' : symdump = 1; break;
#endif
#ifdef TRACING
		case 't' : env.debugging = 2; break;
#endif
#ifdef SETTINGS
		case 'u' : ptr = &argv[i][j + 1];
			   env.undeferror = atoi(ptr);	/* numeric payload */
			   env.undeferror_set = 1;
			   ch = *ptr;			/* first digit */
			   while (isdigit(ch)) {
			       j++;			/* point last digit */
			       ptr++;
			       ch = *ptr;
			   }
			   break;
#endif
#ifdef COPYRIGHT
		case 'v' : verbose = 0; break;
#endif
#ifdef OVERWRITE
		case 'w' : env.overwrite = 0; break;
#endif
#ifdef STATS
		case 'x' : env.statistics = 1; break;
#endif
#if YYDEBUG
		case 'y' : yydebug = 1; break;
#endif
#if ALARM
		case 'z' : env.alarming = 1; break;
#endif
		default  : unknown = argv[i][j]; break;
		} /* end switch */
	    } /* end for */
#if defined(BYTECODE) || defined(COMPILER)
next_parm:
#endif
	    /*
		Overwrite the options with subsequent parameters. Index i is
		decreased, because the next parameter is copied to the current
		index and i is increased in the for-loop.
	    */
	    for (--argc, j = i--; j < argc; j++)
		argv[j] = argv[j + 1];
	} /* end if */
    } /* end for */

    /*
     *  Look for a possible filename parameter. Filenames cannot start with -
     *  and cannot start with a digit, unless preceded by a path: e.g. './'.
     */
    for (i = 1; i < argc; i++) {
	ch = argv[i][0];
	if (!isdigit(ch)) {
	    /*
	     *  If the filename parameter has no extension or an extension that
	     *  differs from .joy, it is assumed to be a binary file.
	     */
	    if (!joy) {
		if ((ptr = strrchr(argv[i], '.')) == argv[i])
		    ptr = 0;
		if (ptr) {
#ifdef BYTECODE
		    if (!strcmp(ptr, ".bic"))	/* extension .bic */
			skip = 0;
#endif
		    if (!strcmp(ptr, ".joy"))	/* extension .joy */
			joy = 1;
		}
	    }
	    if ((yyin = fopen(argv[i], joy ? "r" : "rb")) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n", argv[i]);
		return 0;
	    }
	    /*
	     *  Overwrite argv[0] with the filename.
	     */
	    if ((ptr = strrchr(argv[0] = env.filename = argv[i], '/')) != 0) {
		*ptr++ = 0;
		argv[0] = env.filename = ptr;
	    }
	    /*
		Overwrite the filename with subsequent parameters.
	    */
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    /*
	     *  Only one possible filename is read. Subsequent names are
	     *  passed on to joy.
	     */
	    break;
	} /* end if */
    } /* end for */

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
#ifdef BYTECODE
    if (tablesize() != 256) {
	fprintf(stderr, "error: wrong tablesize\n");
	return 0;
    }
#endif
    if (helping)
	options(&env);		/* might print symbol table */
    if (unknown)
	unknown_opt(&env, exe, unknown);
    inilinebuffer(&env);
    inisymboltable(&env);
#ifdef BYTECODE
    if (listing)
	dumpbytes(&env, skip);	/* calls quit_; might print symbol table */
    if (env.bytecoding) {
	if (joy)
	    initbytes(&env);	/* create .bic file; uses symtab and filename */
	else {
	    rewritebic(filename);
	    quit_(&env);	/* quit_ might print symbol table */
	}
    }
#endif
#ifdef COMPILER
    if (env.compiling)
	initcompile(&env);	/* uses symtab and filename */
#endif
    env.stck = pvec_init();	/* start with an empty stack */
#ifdef KEYBOARD
    if (raw)
	enableRawMode(&env);	/* needs to be done only once */
    else
#endif
    setbuf(stdout, 0);		/* necessary when writing to a pipe */
    setjmp(begin);		/* return here after error or abort */
    env.prog = pvec_init();	/* restart with an empty program */
#ifdef BYTECODE
    if (!joy)			/* process .bic file instead of .joy file */
	readbytes(&env, skip);	/* calls quit_; might print symbol table */
#endif
    if (mustinclude) {
	mustinclude = 0;	/* try including only once */
	include(&env, "usrlib.joy");
	fflush(stdout);		/* flush include messages */
    }
    return yyparse(&env);
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = my_main;

    bottom_of_stack = (char *)&argc;
    GC_INIT();
    return (*m)(argc, argv);
}
