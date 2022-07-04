/*
    module  : initsym.c
    version : 1.19
    date    : 06/19/22
*/
#include "globals.h"

extern FILE *yyin;
clock_t startclock;
FILE *outfp, *declfp;
char **g_argv;
int g_argc, library, compiling, debugging, interpreter;
int autoput = INIAUTOPUT, tracegc = INITRACEGC, undeferror = INIUNDEFERR;

/*
    copyright - report copyright and compilation date and time.
*/
static void copyright(void)
{
    printf("JOY  -  compiled at %s on %s", __TIME__, __DATE__);
    printf(JVERSION ? " (%s)\n" : "\n", JVERSION);
    printf("Copyright 2001 by Manfred von Thun\n");
}

/*
    Test whether it is the interpreter that is executing.
*/
static int is_interpreter(char *argv)
{
    char *ptr;

    if ((ptr = strrchr(argv, '/')) != 0)
	ptr++;
    else
	ptr = argv;
    return !strncmp(ptr, "joy", 3);
}

/*
    options - print help on startup options and exit: options are those that
	      cannot be set from within the language itself.
*/
static void options(void)
{
    printf("Usage: joy [options] [filename] [parameters]\n");
    printf("options, filename, parameters can be given in any order\n");
    printf("options start with '-' and are all given together\n");
    printf("parameters start with a digit\n");
    printf("the filename parameter cannot start with '-' or a digit\n");
    printf("Options:\n");
    printf("  -h : print this help text and exit\n");
    if (interpreter)
	printf("  -c : compile with compile time evaluation\n");
    printf("  -d : print a trace of program execution\n");
    if (interpreter)
	printf("  -l : compile in library mode\n");
    printf("  -s : dump user-defined functions after execution\n");
    printf("  -v : print a copyright notice\n");
    exit(0);
}

void initsym(pEnv env, int argc, char **argv)
{
    char *filename;
    int i, j, helping = 0, symdump = 0, verbose = 0;

    startclock = clock();
    setechoflag(INIECHOFLAG);
    interpreter = is_interpreter(argv[0]);
/*
    First look for options. They start with -.
*/
    for (i = 0; i < argc; i++)
	if (argv[i][0] == '-') {
	    for (j = 1; argv[i][j]; j++)
		switch (argv[i][j]) {
		case 'c': compiling = 1; break;
		case 'd': debugging = 1; break;
		case 'h': helping = 1; break;
		case 'l': library = compiling = 1; break;
		case 's': symdump = 1; break;
		case 'v': verbose = 1; break;
		}
/*
    Overwrite the options with subsequent parameters.
*/
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    break;
	}
/*
    Look for a possible filename parameter. Filenames cannot start with -
    and cannot start with a digit.
*/
    for (i = 1; i < argc; i++)
	if (!isdigit(argv[i][0])) {
	    if ((yyin = freopen(filename = argv[i], "r", stdin)) == 0) {
		fprintf(stderr, "failed to open the file '%s'.\n", filename);
		exit(0);
	    }
/*
    Overwrite argv[0] with the filename and shift subsequent parameters.
*/
	    argv[0] = filename;
	    for (--argc; i < argc; i++)
		argv[i] = argv[i + 1];
	    break;
	}
    g_argc = argc;
    g_argv = argv;
    if (verbose)
	copyright();
    if (symdump)
	my_atexit(dump_table);
    if (helping)
	options();
    inilinebuffer();
}
