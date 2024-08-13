/*
 *  module  : main.c
 *  version : 1.46
 *  date    : 08/12/24
 */
#include "globals.h"

extern FILE *yyin;			/* lexr.c */

static jmp_buf begin;			/* restart with empty program */

char *bottom_of_stack;			/* used in gc.c */

static void stats(pEnv env);
static void dump(pEnv env);

/*
 * abort execution and restart reading from yyin. In the NOBDW version the
 * stack is cleared as well.
 */
void abortexecution_(int num)
{
    fflush(stdin);
    longjmp(begin, num);
}

/*
 * options - print help on startup options and exit: options are those that
 *	     cannot be set from within the language itself.
 */
static void options(void)
{
    printf("JOY  -  compiled at %s on %s", __TIME__, __DATE__);
#ifdef VERS
    printf(" (%s)", VERS);
#endif
    printf("\nCopyright 2001 by Manfred von Thun\n");
    printf("Usage: joy (options | filenames | parameters)*\n");
    printf("options, filenames, parameters can be given in any order\n");
    printf("options start with '-' and parameters start with a digit\n");
    printf("filenames can be preceded by a pathname: e.g. './'\n");
#ifdef COMP
    printf("Compile flags: %s\n", COMP);
#endif
#ifdef LINK
    printf("Linker flags: %s\n", LINK);
#endif
    printf("Options:\n");
    printf("  -a : set the autoput flag (0-2)\n");
#ifdef BYTECODE
    printf("  -b : compile a joy program to bytecode\n");
    printf("  -c : compile joy source into C source\n");
#endif
    printf("  -d : print a trace of stack development\n");
    printf("  -e : set the echoflag (0-3)\n");
#ifdef BYTECODE
    printf("  -f : display a byte code file and exit\n");
#endif
    printf("  -g : set the __tracegc flag (0-6)\n");
    printf("  -h : print this help text and exit\n");
    printf("  -i : ignore impure functions\n");
#if 0
    printf("  -j : filename parameter is binary\n");
#endif
#ifdef KEYBOARD
    printf("  -k : allow keyboard input in raw mode\n");
#endif
    printf("  -l : do not read usrlib.joy at startup\n");
#if 0
    printf("  -m : set maximum limit of data stack\n");
    printf("  -n : limit the number of operations\n");
    printf("  -o : name of output file/function\n");
#endif
    printf("  -p : print debug list of tokens\n");
#if 0
    printf("  -q : operate in quiet mode\n");
#endif
    printf("  -r : print without using recursion\n");
    printf("  -s : dump symbol table after execution\n");
    printf("  -t : print a trace of program execution\n");
    printf("  -u : set the undeferror flag (0,1)\n");
#if 0
    printf("  -v : do not print a copyright notice\n");
#endif
    printf("  -w : no warnings: overwriting, arities\n");
    printf("  -x : print statistics at end of program\n");
#if YYDEBUG
    printf("  -y : print a trace of parser execution\n");
#endif
#if ALARM
    printf("  -z : time out after %d seconds\n", ALARM);
#endif
}

static void unknown_opt(char *exe, int ch)
{
    printf("Unknown option argument: \"-%c\"\n", ch);
    printf("More info with: \"%s -h\"\n", exe);
}

int my_main(int argc, char **argv)
{
/*
 * These variables need to be static because of an intervening longjmp.
 */
    static unsigned char psdump = 0, pstats = 0, joy = 1;
#ifdef BYTECODE
    unsigned char listing = 0;
#endif

    Env env;				/* global variables */
    int i, j, ch, rv;
    char *ptr, *tmp, *exe;
/*
 * A number of flags can be handled within the main function; no need to pass
 * them to subordinate functions.
 */
    unsigned char helping = 0, unknown = 0, mustinclude = 1;
#ifdef KEYBOARD
    unsigned char raw = 0;
#endif

    memset(&env, 0, sizeof(env));
    /*
     * Start the clock.
     */
    env.startclock = clock();
    /*
     * Initialize yyin and other environmental parameters.
     */
    yyin = stdin;
    env.filename = "stdin";
    /*
     * establish pathname, to be used when loading libraries, and basename.
     */
    ptr = strrchr(exe = argv[0], '/');
#ifdef _MSC_VER
    if (!ptr)
	ptr = strrchr(argv[0], '\\');
#endif
    if (ptr) {
	env.pathname = argv[0];		/* split argv[0] in pathname */
	*ptr++ = 0;
	argv[0] = exe = ptr;		/* and basename */
    }
    /*
     * These flags are initialized here, allowing them to be overruled by the
     * command line. When set on the command line, they can not be overruled
     * in the source code.
     */
    env.autoput = INIAUTOPUT;
    env.echoflag = INIECHOFLAG;
    env.undeferror = INIUNDEFERROR;
    env.tracegc = INITRACEGC;
    env.overwrite = INIWARNING;
    /*
     * First look for options. They start with -.
     */
    for (i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
	    for (j = 1; argv[i][j]; j++) {
		switch (argv[i][j]) {
		case 'a' : ptr = &argv[i][j + 1];
			   env.autoput = strtoll(ptr, &tmp, 0);
			   j += tmp - ptr;
			   env.autoput_set = 1;		/* disable usrlib.joy */
			   break;
#ifdef BYTECODE
		case 'b' : env.bytecoding = 2; break;	/* prepare & suspend */
		case 'c' : env.compiling = 2; break;	/* prepare & suspend */
#endif
		case 'd' : env.debugging = 1; break;
		case 'e' : ptr = &argv[i][j + 1];
			   env.echoflag = strtoll(ptr, &tmp, 0);
			   j += tmp - ptr;
			   break;
#ifdef BYTECODE
		case 'f' : listing = 1; break;
#endif
		case 'g' : ptr = &argv[i][j + 1];
			   env.tracegc = strtoll(ptr, &tmp, 0);
			   j += tmp - ptr;
			   break;
		case 'h' : helping = 1; break;
		case 'i' : env.ignore = 1; break;
#if 0
		case 'j' : joy = 0; break;		/* enforce binary */
#endif
#ifdef KEYBOARD
		case 'k' : raw = 1; break;		/* terminal raw mode */
#endif
		case 'l' : mustinclude = 0; break;	/* include usrlib.joy */
#if 0
		case 'm' : ptr = &argv[i][j + 1];
			   env.maximum = strtod(ptr, &tmp);
			   j += tmp - ptr;
			   break;
		case 'n' : ptr = &argv[i][j + 1];
			   env.operats = strtod(ptr, &tmp);
			   j += tmp - ptr;
			   break;
		case 'o' : filename = &argv[i][j + 1];	/* string payload */
			   goto next_parm;
#endif
		case 'p' : env.printing = 1; break;
#if 0
		case 'q' : env.quiet = 1; break;
#endif
		case 'r' : env.recurse = 1; break;
		case 's' : psdump = 1; break;
		case 't' : env.debugging = 2; break;
		case 'u' : ptr = &argv[i][j + 1];
			   env.undeferror = strtoll(ptr, &tmp, 0);
			   j += tmp - ptr;
			   env.undeferror_set = 1;	/* disable usrlib.joy */
			   break;
#if 0
		case 'v' : verbose = 0; break;
#endif
		case 'w' : remove("joy.log"); env.overwrite = 0; break;
		case 'x' : pstats = 1; break;
#if YYDEBUG
		case 'y' : yydebug = 1; break;
#endif
#if ALARM
		case 'z' : env.alarming = 1; break;
#endif
		default  : unknown = argv[i][j]; break;
		} /* end switch */
	    } /* end for */
#if 0
next_parm:
#endif
	    /*
	     * Overwrite the option(s) with subsequent parameters. Index i is
	     * decreased, because the next parameter is copied to the current
	     * index and i is increased in the for-loop.
	     */
	    for (--argc, j = i--; j < argc; j++)
		argv[j] = argv[j + 1];
	} /* end if */
    } /* end for */
    /*
     * Look for a possible filename parameter. Filenames cannot start with -
     * and cannot start with a digit, unless preceded by a path: e.g. './'.
     */
    for (i = 1; i < argc; i++) {
	ch = argv[i][0];
	if (!isdigit(ch)) {
	    /*
	     * If the filename parameter has no extension or an extension that
	     * differs from .joy, it is assumed to be a binary file.
	     */
#ifdef BYTECODE
	    if (joy) {
		if ((ptr = strrchr(argv[i], '.')) == 0 || strcmp(ptr, ".joy"))
		    mustinclude = joy = 0;
	    }
#endif
	    if ((yyin = fopen(argv[i], joy ? "r" : "rb")) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n", argv[i]);
		return 0;
	    }
	    /*
	     * Overwrite argv[0] with the filename.
	     */
	    if ((ptr = strrchr(argv[0] = env.filename = argv[i], '/')) != 0) {
		*ptr++ = 0;
		argv[0] = env.filename = ptr;
	    }
	    /*
	     * Overwrite the filename with subsequent parameters.
	     */
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    /*
	     * Only one possible filename is read. Subsequent names are
	     * passed on to joy.
	     */
	    break;
	} /* end if */
    } /* end for */
    inilinebuffer(&env);
    /*
     * determine argc and argv.
     */
    env.g_argc = argc;
    env.g_argv = argv;
    /*
     * initialize vectors.
     */
    vec_init(env.tokens);
    vec_init(env.symtab);
    env.stck = pvec_init();		/* start with an empty stack */
#ifdef USE_MULTI_THREADS_JOY
    vec_init(env.context);
    vec_init(env.channel);
#endif
    /*
     * initialize symbol table.
     */
    inisymboltable(&env);
    /*
     * handle options, might print symbol table.
     */
    if (helping || unknown) {
	helping ? options() : unknown_opt(exe, unknown);
	goto einde;
    }
#ifdef BYTECODE
    if (listing) {
	dumpbytes(&env);		/* display .bic or .bjc file */
	goto einde;
    }
    if (env.bytecoding) {
	if (joy)
	    initbytes(&env);		/* create .bic file */
	else {
	    rewritebic(&env);		/* create .bjc file */
	    goto einde;
	}
    }
    if (env.compiling)
	initcompile(&env);		/* create .c file */
#endif
    /*
     * initialize stack before SetRaw.
     */
    env.stck = pvec_init();		/* and empty stack */
    /*
     * initialize standard input and output.
     */
#ifdef KEYBOARD
    if (raw && strcmp(env.filename, "stdin")) {	/* raw requires a filename */
	env.autoput = 0;		/* disable autoput and usrlib.joy */
	env.autoput_set = 1;		/* prevent enabling autoput */
	SetRaw(&env);
    } else				/* keep output buffered */
#endif
	setbuf(stdout, 0);		/* disable output buffering (pipe) */
    /*
     * read initial library.
     */
    if (mustinclude)
	include(&env, "usrlib.joy");	/* start reading from library first */
    rv = setjmp(begin);			/* return here after error or abort */
    if (rv == ABORT_ERROR && joy)	/* in case of a runtime error ...   */
	trace(&env, stderr);		/* ... dump stack and (all of) code */
    if (rv == ABORT_QUIT || (rv && !joy))	/* in case end of file ...  */
	goto einde;				/* ... wrap up and exit     */
    /*
     * (re)initialize code. The stack is left as it is.
     */
    env.prog = pvec_init();		/* restart with an empty program */
    if (joy)
	yyparse(&env);
#ifdef BYTECODE
    else				/* process .bic file instead of .joy */
	readbytes(&env, env.compiling ? 0 : 1);
#endif
einde:
#ifdef BYTECODE
    if (env.bytecoding)
	exitbytes(&env);
    if (env.compiling)
	exitcompile(&env);
#endif
    /*
     * This is the location where statistics and the symbol table can be
     * printed.
     */
    if (pstats)
	stats(&env);
    if (psdump)
	dump(&env);
    return 0;
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = my_main;

    bottom_of_stack = (char *)&argc;
    GC_INIT();
    return (*m)(argc, argv);
}

/*
 * print statistics.
 */
static void stats(pEnv env)
{
    printf("%.0f milliseconds CPU\n", (clock() - env->startclock) * 1000.0 /
	   CLOCKS_PER_SEC);
    printf("%d data nodes available\n", pvec_max(env->stck));
    printf("%d code nodes available\n", pvec_max(env->prog));
    printf("%.0f garbage collections\n", (double)GC_get_gc_no());
    printf("%.0f calls to joy interpreter\n", env->calls);
    printf("%.0f operations executed\n", env->opers);
}

/*
 * dump the symbol table, from last to first.
 */
static void dump(pEnv env)
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
