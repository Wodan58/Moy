/*
 *  module  : main.c
 *  version : 1.2
 *  date    : 07/12/23
 */
#include "globals.h"

#define ERROR_ON_USRLIB 0

extern FILE *yyin;

static jmp_buf begin;

/*
    abort execution and restart reading from yyin. In the NOBDW version the
    stack is cleared as well.
*/
PUBLIC void abortexecution_(void)
{
    longjmp(begin, 1);
}

/*
    print a runtime error to stderr and abort the execution of current program.
*/
PUBLIC void execerror(char *message, char *op)
{
    int leng = 0;
    char *ptr, *str;

    if ((ptr = strrchr(op, '/')) != 0)
        ptr++;
    else
        ptr = op;
    if ((str = strrchr(ptr, '.')) != 0 && str[1] == 'c')
        leng = str - ptr;
    else
        leng = strlen(ptr);
    fflush(stdout);
    fprintf(stderr, "run time error: %s needed for %.*s\n", message, leng, ptr);
    abortexecution_();
}

/*
    fatal terminates the program after a stack overflow, likely to result in
    heap corruption that makes it impossible to continue. And exit instead of
    _exit may fail too.
*/
#ifdef SIGNAL_HANDLING
PRIVATE void fatal(void)
{
    fflush(stdout);
    fprintf(stderr, "fatal error: memory overflow\n");
    exit(EXIT_FAILURE);
}
#endif

/*
    report_clock - report the amount of time spent.
*/
#ifdef STATS
PRIVATE void report_clock(pEnv env)
{
    double timediff;

    timediff = (clock() - env->startclock) / CLOCKS_PER_SEC;
    fprintf(stderr, "%.2f seconds CPU to execute\n", timediff);
}
#endif

/*
 *  copyright - Print all copyright notices, even historical ones.
 *
 *  The version must be set on the commandline when compiling:
 *  -DJVERSION="\"alpha\"" or whatever.
 */
PRIVATE void copyright(char *file)
{
    int i, j = 0;
    char str[INPLINEMAX], *ptr;

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

    if (file) {
        if ((ptr = strrchr(file, '/')) != 0)
            file = ptr + 1;
        for (i = 0; table[i].file; i++) {
            if (!strcmp(file, table[i].file)) {
                strftime(str, sizeof(str), "%H:%M:%S on %b %e %Y",
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

/*
    dump the symbol table - accessed from quit_, because env is needed;
    do this only for user defined symbols.
*/
PRIVATE void dump_table(pEnv env)
{
    int i;
    Entry ent;

    for (i = sym_size(env->symtab) - 1; i >= 0; i--) {
        ent = sym_at(env->symtab, i);
        if (!ent.is_user)
            break;
        printf("(%d) %s == ", i, ent.name);
        writeterm(env, ent.u.body);
        putchar('\n');
    }
}

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
#ifdef TRACING
    printf("  -d : print a trace of program execution\n");
#endif
    printf("  -s : dump user-defined functions after execution\n");
    printf("  -v : do not print a copyright notice\n");
    printf("  -w : suppress warnings about overwriting builtin\n");
#if YYDEBUG
    printf("  -y : print a trace of parser execution\n");
#endif
    exit(EXIT_SUCCESS);
}

PRIVATE int my_main(int argc, char **argv)
{
    static unsigned char mustinclude = 1;
    int i, j, ch;
    char *filename = 0, *ptr;
    unsigned char verbose = 1, symdump = 0, helping = 0;

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
    vec_init(env.stck);
    vec_init(env.prog);
    sym_init(env.symtab);
    env.overwrite = INIWARNING;
    /*
     *  Initialize yyin and other environmental parameters.
     */
    yyin = stdin;
    if ((ptr = strrchr(env.pathname = argv[0], '/')) != 0)
        *ptr = 0;
    else
        env.pathname = ".";
    /*
     *  First look for options. They start with -.
     */
    for (i = 1; i < argc; i++)
        if (argv[i][0] == '-') {
            for (j = 1; argv[i][j]; j++)
                switch (argv[i][j]) {
#ifdef TRACING
                case 'd' : env.debugging = 1; break;
#endif
                case 'h' : helping = 1; break;
                case 's' : symdump = 1; break;
                case 'v' : verbose = 0; break;
                case 'w' : env.overwrite = 0; break;
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
            if ((yyin = freopen(filename = argv[i], "r", stdin)) == 0) {
                fprintf(stderr, "failed to open the file '%s'.\n", filename);
                return 0;
            }
            /*
             *  Overwrite argv[0] with the filename and shift subsequent
             *  parameters. Also change directory to that filename.
             */
            if ((ptr = strrchr(argv[0] = filename, '/')) != 0) {
                *ptr++ = 0;
                argv[0] = filename = ptr;
            }
            for (--argc; i < argc; i++)
                argv[i] = argv[i + 1];
            break;
        }
    }
    env.g_argc = argc;
    env.g_argv = argv;
    if (verbose)
        copyright(filename);
    if (symdump)
        my_atexit(dump_table);
    if (helping)
        options();
    env.echoflag = INIECHOFLAG;
    env.autoput = INIAUTOPUT;
    env.undeferror = INIUNDEFERROR;
#ifdef REMEMBER_FILENAME
    inilinebuffer(filename);
#else
    inilinebuffer();
#endif
    inisymboltable(&env);
    setjmp(begin);
    if (mustinclude) {
        mustinclude = 0;
        include(&env, "usrlib.joy", ERROR_ON_USRLIB);
    }
    return yyparse(&env);
}

int main(int argc, char **argv)
{
    int (*volatile m)(int, char **) = my_main;

#ifdef GC_BDW
    GC_INIT();
#else
#ifdef SIGNAL_HANDLING
    GC_init(&argc, fatal);
#else
    GC_init(&argc);
#endif
#endif
    return (*m)(argc, argv);
}
