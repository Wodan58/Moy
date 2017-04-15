/*
    module  : interp.c
    version : 1.3
    date    : 04/15/17
*/
#ifdef RUNTIME
#include "runtime.c"
#else
#include "runtime.h"
#endif

#if 0
#define TRACE
#define DEBUG
#endif

#ifndef RUNTIME
static unsigned direct;
#endif

void interprete(Node *code)
{
    Entry *sym;
    Node *node;
#ifndef RUNTIME
    char *name;
#endif

start:
#ifdef DEBUG
    fprintf(stderr, "code: ");
    writeterm(code, stderr);
    fprintf(stderr, ";\n");
#endif
    for (; code; code = code->next) {
#ifdef TRACE
	writestack(stk, stderr);
	fprintf(stderr, " . ");
	writeterm(code, stderr);
	fprintf(stderr, "\n");
#endif
	switch (code->op) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case STRING_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	case SYMBOL_:
#ifndef RUNTIME
	    if (optimizing) {
		if (code->op == LIST_ && code->u.lis)
		    add_history2(LIST_, code->u.lis->op);
		else
		    add_history(code->op);
	    }
#endif
	    DUPLICATE(code);
	    break;
	case USR_:
	    sym = code->u.ent;
	    if ((node = sym->u.body) == 0 && undeferror)
		execerror("definition", sym->name);
	    else if (node && (sym->flags & IS_BUILTIN))
		(*sym->u.proc)();
	    else if (node) {
#ifndef RUNTIME
		if (compiling) {
		    if (direct)
			printstack(outfp);
		    if ((sym->flags & IS_ACTIVE) == 0) {
			sym->flags |= IS_ACTIVE;
			interprete(node);
			sym->flags &= ~IS_ACTIVE;
		    } else {
			sym->flags |= IS_USED;
			name = usrname(sym->name);
			fprintf(outfp, "void do_%s(void);", name);
			fprintf(outfp, "do_%s();", name);
		    }
		    break;
		}
#endif
		if (!code->next) {
		    code = node;
		    goto start;
		}
		interprete(node);
	    }
	    continue;
	case ANON_FUNCT_:
	    (*code->u.proc)();
	    break;
	case DO_BINREC:
	    do_binrec();
	    break;
	case DO_SMALL:
	    do_small();
	    break;
	case DO_PRED:
	    do_pred();
	    break;
	case DO_DUP:
	    do_dup();
	    break;
	case DO_PLUS:
	    do_plus();
	    break;
	case DO_MUL:
	    do_mul();
	    break;
	case DO_EQL:
	    do_eql();
	    break;
	case DO_GREATER:
	    do_greater();
	    break;
	case DO_OR:
	    do_or();
	    break;
	case DO_AND:
	    do_and();
	    break;
	case DO_NOT:
	    do_not();
	    break;
	case DO_SWAP:
	    do_swap();
	    break;
	case DO_STEP:
	    do_step();
	    break;
	case DO_CONS:
	    do_cons();
	    break;
	case DO_DIP:
	    do_dip();
	    break;
	case DO_I:
	    do_i();
	    break;
	case DO_UNCONS:
	    do_uncons();
	    break;
	case DO_POP:
	    do_pop();
	    break;
	case DO_NOTHING:
	    do_nothing();
	    break;
	case DO_SAMETYPE:
	    do_sametype();
	    break;
	case DO_INDEX:
	    do_index();
	    break;
	case DO_PUT:
	    do_put();
	    break;
	case DO_PUTCH:
	    do_putch();
	    break;
	case DO_GET:
	    do_get();
	    break;
	case DO_STACK:
	    do_stack();
	    break;
	case DO_UNSTACK:
	    do_unstack();
	    break;
	case DO_BODY:
	    do_body();
	    break;
	case DO_LEQL:
	    do_leql();
	    break;
	case DO_SETAUTOPUT:
	    do_setautoput();
	    break;
	case DO_SETUNDEFERROR:
	    do_setundeferror();
	    break;
	case DO_ARGV:
	    do_argv();
	    break;
	case DO_REST:
	    do_rest();
	    break;
	case DO_MAP:
	    do_map();
	    break;
	case DO_STRTOL:
	    do_strtol();
	    break;
	case DO_WHILE:
	    do_while();
	    break;
	case DO_ROLLUP:
	    do_rollup();
	    break;
	case DO_REM:
	    do_rem();
	    break;
	case DO_QUIT:
	    do_quit();
	    break;
	case DO_SETECHO:
	    do_setecho();
	    break;
	case DO_MINUS:
	    do_minus();
	    break;
	case DO_SUCC:
	    do_succ();
	    break;
	case DO_CONCAT:
	    do_concat();
	    break;
	case DO_ABS:
	    do_abs();
	    break;
	case DO_DUPD:
	    do_dupd();
	    break;
	case DO_SWAPD:
	    do_swapd();
	    break;
	case DO_CLEAVE:
	    do_cleave();
	    break;
	case DO_UNARY2:
	    do_unary2();
	    break;
	case DO_DIVIDE:
	    do_divide();
	    break;
	case DO_ARGC:
	    do_argc();
	    break;
	case DO_TIME:
	    do_time();
	    break;
	case DO_SRAND:
	    do_srand();
	    break;
	case DO_OF:
	    do_of();
	    break;
	case DO_FIRST:
	    do_first();
	    break;
	case DO_PUTCHARS:
	    do_putchars();
	    break;
	case DO_INTEGER:
	    do_integer();
	    break;
	case DO_IFTE:
	    do_ifte();
	    break;
	case DO_EQUAL:
	    do_equal();
	    break;
	case DO_AT:
	    do_at();
	    break;
	case DO_LIST:
	    do_list();
	    break;
	case DO_SOME:
	    do_some();
	    break;
	case DO_SIZE:
	    do_size();
	    break;
	case DO_GEQL:
	    do_geql();
	    break;
	case DO_TIMES:
	    do_times();
	    break;
	case DO_LINREC:
	    do_linrec();
	    break;
	case DO_NULL:
	    do_null();
	    break;
	case DO_NULLARY:
	    do_nullary();
	    break;
	case DO_LESS:
	    do_less();
	    break;
	case DO_INFRA:
	    do_infra();
	    break;
	case DO_SETTRACEGC:
	    do_settracegc();
	    break;
	case DO_POPD:
	    do_popd();
	    break;
	case DO_ID:
	    do_id();
	    break;
	case DO_SWONS:
	    do_swons();
	    break;
	case DO_SIN:
	    do_sin();
	    break;
	case DO_COS:
	    do_cos();
	    break;
	case DO_TAN:
	    do_tan();
	    break;
	case DO_XOR:
	    do_xor();
	    break;
	case DO_FOLD:
	    do_fold();
	    break;
	case DO_UNSWONS:
	    do_unswons();
	    break;
	case DO_ROLLDOWN:
	    do_rolldown();
	    break;
	case DO_LOG10:
	    do_log10();
	    break;
	case DO_UNARY:
	    do_unary();
	    break;
	case DO_SPLIT:
	    do_split();
	    break;
	case DO_ENCONCAT:
	    do_enconcat();
	    break;
	case DO_COND:
	    do_cond();
	    break;
	case DO_IN:
	    do_in();
	    break;
	case DO_FILTER:
	    do_filter();
	    break;
	case DO_ROLLUPD:
	    do_rollupd();
	    break;
	case DO_IFLIST:
	    do_iflist();
	    break;
	case DO_INTERN:
	    do_intern();
	    break;
	case DO_OPCASE:
	    do_opcase();
	    break;
	case DO_HAS:
	    do_has();
	    break;
	case DO_FLOAT:
	    do_float();
	    break;
	case DO_STRING:
	    do_string();
	    break;
	case DO_TAILREC:
	    do_tailrec();
	    break;
	case DO_CASE:
	    do_case();
	    break;
	case DO_LEAF:
	    do_leaf();
	    break;
	case DO_INCLUDE:
	    do_include();
	    break;
	case DO_ABORT:
	    do_abort();
	    break;
	case DO_X:
	    do_x();
	    break;
	case DO_CONDNESTREC:
	    do_condnestrec();
	    break;
	case DO_CONDLINREC:
	    do_condlinrec();
	    break;
	case DO_ROTATE:
	    do_rotate();
	    break;
	case DO_FALSE:
	    do_false();
	    break;
	case DO_TRUE:
	    do_true();
	    break;
	case DO_MAXINT:
	    do_maxint();
	    break;
	case DO_SETSIZE:
	    do_setsize();
	    break;
	case DO_SYMTABMAX:
	    do_symtabmax();
	    break;
	case DO_SYMTABINDEX:
	    do_symtabindex();
	    break;
	case DO_DUMP:
	    do_dump();
	    break;
	case DO_CONTS:
	    do_conts();
	    break;
	case DO_AUTOPUT:
	    do_autoput();
	    break;
	case DO_UNDEFERROR:
	    do_undeferror();
	    break;
	case DO_UNDEFS:
	    do_undefs();
	    break;
	case DO_ECHO:
	    do_echo();
	    break;
	case DO_CLOCK:
	    do_clock();
	    break;
	case DO_RAND:
	    do_rand();
	    break;
	case DO_MEMORYMAX:
	    do_memorymax();
	    break;
	case DO_STDIN:
	    do_stdin();
	    break;
	case DO_STDOUT:
	    do_stdout();
	    break;
	case DO_STDERR:
	    do_stdout();
	    break;
	case DO_ROLLDOWND:
	    do_rolldownd();
	    break;
	case DO_ROTATED:
	    do_rotated();
	    break;
	case DO_CHOICE:
	    do_choice();
	    break;
	case DO_DIV:
	    do_div();
	    break;
	case DO_SIGN:
	    do_sign();
	    break;
	case DO_NEG:
	    do_neg();
	    break;
	case DO_ORD:
	    do_ord();
	    break;
	case DO_CHR:
	    do_chr();
	    break;
	case DO_ASIN:
	    do_asin();
	    break;
	case DO_ACOS:
	    do_acos();
	    break;
	case DO_ATAN:
	    do_atan();
	    break;
	case DO_ATAN2:
	    do_atan2();
	    break;
	case DO_CEIL:
	    do_ceil();
	    break;
	case DO_SINH:
	    do_sinh();
	    break;
	case DO_COSH:
	    do_cosh();
	    break;
	case DO_TANH:
	    do_tanh();
	    break;
	case DO_EXP:
	    do_exp();
	    break;
	case DO_FLOOR:
	    do_floor();
	    break;
	case DO_ROUND:
	    do_round();
	    break;
	case DO_FREXP:
	    do_frexp();
	    break;
	case DO_LDEXP:
	    do_ldexp();
	    break;
	case DO_LOG:
	    do_log();
	    break;
	case DO_MODF:
	    do_modf();
	    break;
	case DO_POW:
	    do_pow();
	    break;
	case DO_SQRT:
	    do_sqrt();
	    break;
	case DO_TRUNC:
	    do_trunc();
	    break;
	case DO_LOCALTIME:
	    do_localtime();
	    break;
	case DO_GMTIME:
	    do_gmtime();
	    break;
	case DO_MKTIME:
	    do_mktime();
	    break;
	case DO_STRFTIME:
	    do_strftime();
	    break;
	case DO_STRTOD:
	    do_strtod();
	    break;
	case DO_FORMAT:
	    do_format();
	    break;
	case DO_FORMATF:
	    do_formatf();
	    break;
	case DO_MIN:
	    do_min();
	    break;
	case DO_MAX:
	    do_max();
	    break;
	case DO_COMPARE:
	    do_compare();
	    break;
	case DO_DROP:
	    do_drop();
	    break;
	case DO_TAKE:
	    do_take();
	    break;
	case DO_NAME:
	    do_name();
	    break;
	case DO_NEQL:
	    do_neql();
	    break;
	case DO_CHAR:
	    do_char();
	    break;
	case DO_LOGICAL:
	    do_logical();
	    break;
	case DO_SET:
	    do_set();
	    break;
	case DO_USER:
	    do_user();
	    break;
	case DO_FILE:
	    do_file();
	    break;
	case DO_IFCHAR:
	    do_ifchar();
	    break;
	case DO_IFFILE:
	    do_iffile();
	    break;
	case DO_IFFLOAT:
	    do_iffloat();
	    break;
	case DO_IFINTEGER:
	    do_ifinteger();
	    break;
	case DO_IFLOGICAL:
	    do_iflogical();
	    break;
	case DO_IFSET:
	    do_ifset();
	    break;
	case DO_IFSTRING:
	    do_ifstring();
	    break;
	case DO_APP1:
	    do_app1();
	    break;
	case DO_APP11:
	    do_app11();
	    break;
	case DO_APP12:
	    do_app12();
	    break;
	case DO_GC:
	    do_gc();
	    break;
	case DO_SYSTEM:
	    do_system();
	    break;
	case DO_GETENV:
	    do_getenv();
	    break;
	case DO_MEMORYINDEX:
	    do_memoryindex();
	    break;
	case DO_GETCH:
	    do_getch();
	    break;
	case DO_ALL:
	    do_all();
	    break;
	case DO_HELP:
	    do_help();
	    break;
	case DO_HELP1:
	    do_help1();
	    break;
	case DO_HELPDETAIL:
	    do_helpdetail();
	    break;
	case DO_MANUAL:
	    do_manual();
	    break;
	case DO_HTML_MANUAL:
	    do_html_manual();
	    break;
	case DO_LATEX_MANUAL:
	    do_latex_manual();
	    break;
	case DO_MANUAL_LIST:
	    do_manual_list();
	    break;
	case DO_CASTING:
	    do_casting();
	    break;
	case DO_BRANCH:
	    do_branch();
	    break;
	case DO_CONSTRUCT:
	    do_construct();
	    break;
	case DO_UNARY3:
	    do_unary3();
	    break;
	case DO_UNARY4:
	    do_unary4();
	    break;
	case DO_BINARY:
	    do_binary();
	    break;
	case DO_TERNARY:
	    do_ternary();
	    break;
	case DO_GENREC:
	    do_genrec();
	    break;
	case DO_PRIMREC:
	    do_primrec();
	    break;
	case DO_TREESTEP:
	    do_treestep();
	    break;
	case DO_TREEREC:
	    do_treerec();
	    break;
	case DO_TREEGENREC:
	    do_treegenrec();
	    break;
	case DO_FCLOSE:
	    do_fclose();
	    break;
	case DO_FEOF:
	    do_feof();
	    break;
	case DO_FERROR:
	    do_ferror();
	    break;
	case DO_FFLUSH:
	    do_fflush();
	    break;
	case DO_FGET:
	    do_fget();
	    break;
	case DO_FGETCH:
	    do_fgetch();
	    break;
	case DO_FGETS:
	    do_fgets();
	    break;
	case DO_FOPEN:
	    do_fopen();
	    break;
	case DO_FREAD:
	    do_fread();
	    break;
	case DO_FWRITE:
	    do_fwrite();
	    break;
	case DO_FREMOVE:
	    do_fremove();
	    break;
	case DO_FRENAME:
	    do_frename();
	    break;
	case DO_FILETIME:
	    do_filetime();
	    break;
	case DO_FPUT:
	    do_fput();
	    break;
	case DO_FPUTCH:
	    do_fputch();
	    break;
	case DO_FPUTCHARS:
	    do_fputchars();
	    break;
	case DO_FSEEK:
	    do_fseek();
	    break;
	case DO_FTELL:
	    do_ftell();
	    break;
	default:
	    printf("unknown: %s\n", opername(code->op));
	    exit(1);
	}
#ifndef RUNTIME
#ifdef TRACE
	prt_history();
#endif
#endif
    }
}

void execute(Node *code)
{
    interprete(code);
    do_stop();
}

#ifndef RUNTIME
void evaluate(Node *code)
{
    NewScope();
    interprete(code);
    printstack(outfp);
    OldScope();
}

void evaluate1(Node *code)
{
    direct = 1;
    evaluate(code);
    direct = 0;
}

void evaluate2(Node *code, int num)
{
    if (num == START_SCOPE || num == INIT_SCOPE)
	NewScope();
    if (num == INIT_SCOPE)
	return;
    if (num != STOP_SCOPE) {
	interprete(code);
	printstack(outfp);
    }
    if (num == END_SCOPE || num == STOP_SCOPE)
	OldScope();
}
#endif
