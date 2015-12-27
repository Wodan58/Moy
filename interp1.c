/*
    module  : interp1.c
    version : 1.1
    date    : 12/27/15
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gc.h>
#include "globals1.h"

PRIVATE void helpdetail_();
PRIVATE void undefs_();
PRIVATE void make_manual(int style /* 0=plain, 1=html, 2=latex */ );
PRIVATE void manual_list_();
PRIVATE void manual_list_aux_();

#define FLOATABLE						\
    (stk->op == INTEGER_ || stk->op == FLOAT_)
#define FLOATABLE2						\
    ((stk->op == FLOAT_ && stk->next->op == FLOAT_) ||		\
     (stk->op == FLOAT_ && stk->next->op == INTEGER_) ||	\
     (stk->op == INTEGER_ && stk->next->op == FLOAT_))
#define FLOATVAL						\
    (stk->op == FLOAT_ ? stk->u.dbl : (double) stk->u.num)
#define FLOATVAL2						\
    (stk->next->op == FLOAT_ ? stk->next->u.dbl : (double) stk->next->u.num)

#define ONEPARAM(NAME)						\
    if (stk == NULL)						\
	execerror("one parameter",NAME)
#define TWOPARAMS(NAME)						\
    if (stk == NULL || stk->next == NULL)			\
	execerror("two parameters",NAME)
#define THREEPARAMS(NAME)					\
    if (stk == NULL || stk->next == NULL			\
		    || stk->next->next == NULL)			\
	execerror("three parameters",NAME)
#define FOURPARAMS(NAME)					\
    if (stk == NULL || stk->next == NULL			\
		    || stk->next->next == NULL			\
		    || stk->next->next->next == NULL)		\
	execerror("four parameters",NAME)
#define FIVEPARAMS(NAME)					\
    if (stk == NULL || stk->next == NULL			\
		    || stk->next->next == NULL			\
		    || stk->next->next->next == NULL		\
		    || stk->next->next->next->next == NULL)	\
	execerror("five parameters",NAME)
#define ONEQUOTE(NAME)						\
    if (stk->op != LIST_)					\
	execerror("quotation as top parameter",NAME)
#define TWOQUOTES(NAME)						\
    ONEQUOTE(NAME);						\
    if (stk->next->op != LIST_)					\
	execerror("quotation as second parameter",NAME)
#define THREEQUOTES(NAME)					\
    TWOQUOTES(NAME);						\
    if (stk->next->next->op != LIST_)				\
	execerror("quotation as third parameter",NAME)
#define FOURQUOTES(NAME)					\
    THREEQUOTES(NAME);						\
    if (stk->next->next->next->op != LIST_)			\
	execerror("quotation as fourth parameter",NAME)
#define SAME2TYPES(NAME)					\
    if (stk->op != stk->next->op)				\
	execerror("two parameters of the same type",NAME)
#define STRING(NAME)						\
    if (stk->op != STRING_)					\
	execerror("string",NAME)
#define STRING2(NAME)						\
    if (stk->next->op != STRING_)				\
	execerror("string as second parameter",NAME)
#define INTEGER(NAME)						\
    if (stk->op != INTEGER_)					\
	execerror("integer",NAME)
#define INTEGER2(NAME)						\
    if (stk->next->op != INTEGER_)				\
	execerror("integer as second parameter",NAME)
#define CHARACTER(NAME)						\
    if (stk->op != CHAR_)					\
	execerror("character",NAME)
#define INTEGERS2(NAME)						\
    if (stk->op != INTEGER_ || stk->next->op != INTEGER_)	\
	execerror("two integers",NAME)
#define NUMERICTYPE(NAME)					\
    if (stk->op != INTEGER_ && stk->op != CHAR_			\
			    && stk->op != BOOLEAN_)		\
	execerror("numeric",NAME)
#define NUMERIC2(NAME)						\
    if (stk->next->op != INTEGER_ && stk->next->op != CHAR_)	\
	execerror("numeric second parameter",NAME)
#define FLOAT(NAME)						\
    if (!FLOATABLE)						\
	execerror("float or integer", NAME);
#define FLOAT2(NAME)						\
    if (!(FLOATABLE2 || (stk->op == INTEGER_ && stk->next->op == INTEGER_))) \
	execerror("two floats or integers", NAME)
#define FILE(NAME)						\
    if (stk->op != FILE_ || stk->u.fil == NULL)			\
	execerror("file", NAME)
#define CHECKZERO(NAME)						\
    if (stk->u.num == 0)					\
	execerror("non-zero operand",NAME)
#define LIST(NAME)						\
    if (stk->op != LIST_)					\
	execerror("list",NAME)
#define LIST2(NAME)						\
    if (stk->next->op != LIST_)					\
	execerror("list as second parameter",NAME)
#define USERDEF(NAME)						\
    if (stk->op != USR_)					\
	execerror("user defined symbol",NAME)
#define CHECKLIST(OPR,NAME)					\
    if (OPR != LIST_)						\
	execerror("internal list",NAME)
#define CHECKSETMEMBER(NODE,NAME)				\
    if ((NODE->op != INTEGER_ && NODE->op != CHAR_) ||		\
	NODE->u.num >= SETSIZE)					\
	execerror("small numeric",NAME)
#define CHECKEMPTYSET(SET,NAME)					\
    if (SET == 0)						\
	execerror("non-empty set",NAME)
#define CHECKEMPTYSTRING(STRING,NAME)				\
    if (*STRING == '\0')					\
	execerror("non-empty string",NAME)
#define CHECKEMPTYLIST(LIST,NAME)				\
    if (LIST == NULL)						\
	execerror("non-empty list",NAME)
#define INDEXTOOLARGE(NAME)					\
    execerror("smaller index",NAME)
#define BADAGGREGATE(NAME)					\
    execerror("aggregate parameter",NAME)
#define BADDATA(NAME)						\
    execerror("different type",NAME)

#define NULLARY(CONSTRUCTOR,VALUE)                              \
    stk = CONSTRUCTOR(VALUE, stk)
#define UNARY(CONSTRUCTOR,VALUE)                                \
    stk = CONSTRUCTOR(VALUE, stk->next)
#define BINARY(CONSTRUCTOR,VALUE)                               \
    stk = CONSTRUCTOR(VALUE, stk->next->next)
#define GNULLARY(TYPE,VALUE)                                    \
    stk = newnode(TYPE,(VALUE),stk)
#define GUNARY(TYPE,VALUE)                                      \
    stk = newnode(TYPE,(VALUE),stk->next)
#define GBINARY(TYPE,VALUE)                                     \
    stk = newnode(TYPE,(VALUE),stk->next->next)
#define GTERNARY(TYPE,VALUE)					\
    stk = newnode(TYPE,(VALUE),stk->next->next->next)

/* - - - -  O P E R A N D S   - - - - */

#define PUSH_PROC(PROCEDURE,CONSTRUCTOR,VALUE)			\
PRIVATE void PROCEDURE()					\
{ PUSH(CONSTRUCTOR, VALUE); }

/* constants */
PUSH_PROC(true_, BOOLEAN_, 1)
PUSH_PROC(false_, BOOLEAN_, 0)
PUSH_PROC(setsize_, INTEGER_, SETSIZE)
PUSH_PROC(maxint_, INTEGER_, MAXINT)
PUSH_PROC(symtabmax_, INTEGER_, SYMTABMAX)
PUSH_PROC(memorymax_, INTEGER_, MEMORYMAX)
PUSH_PROC(stdin_, FILE_, stdin)
PUSH_PROC(stdout_, FILE_, stdout)
PUSH_PROC(stderr_, FILE_, stderr)

/* variables */
PUSH_PROC(dump_, LIST_, 0)
PUSH_PROC(conts_, LIST_, 0)
PUSH_PROC(symtabindex_, INTEGER_, (int)(symtabindex - symtab))
PUSH_PROC(rand_, INTEGER_, rand())
PUSH_PROC(memoryindex_, INTEGER_, stk > memory && stk < &memory[MEMORYMAX] ? \
	  (int)(stk - memory) : 0)
PUSH_PROC(echo_, INTEGER_, echoflag)
PUSH_PROC(autoput_, INTEGER_, autoput)
PUSH_PROC(undeferror_, INTEGER_, undeferror)
PUSH_PROC(clock_, INTEGER_, clock() - startclock)
PUSH_PROC(time_, INTEGER_, (int)time(0))
PUSH_PROC(argc_, INTEGER_, g_argc)

#include "src/stack.c"

/* - - - - -   O P E R A T O R S   - - - - - */

PRIVATE void id_()
{
    /* do nothing */
}

#include "src/unstack.c"

/* - - -   STACK   - - - */

#include "src/name.c"
#include "src/intern.c"
#include "src/getenv.c"
#include "src/body.c"
#include "src/pop.c"
#include "src/swap.c"
#include "src/rollup.c"
#include "src/rolldown.c"
#include "src/rotate.c"
#include "src/dup.c"

#define PROCEDURE	popd_
#define NAME		"popd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	pop_
#include "src/dipped.c"

#define PROCEDURE	dupd_
#define NAME		"dupd"
#define PARAMCOUNT	TWOPARAMS
#define ARGUMENT	dup_
#include "src/dipped.c"

#define PROCEDURE	swapd_
#define NAME		"swapd"
#define PARAMCOUNT	THREEPARAMS
#define ARGUMENT	swap_
#include "src/dipped.c"

#define PROCEDURE	rolldownd_
#define NAME		"rolldownd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	rolldown_
#include "src/dipped.c"

#define PROCEDURE	rollupd_
#define NAME		"rollupd"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	rollup_
#include "src/dipped.c"

#define PROCEDURE	rotated_
#define NAME		"rotated"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	rotate_
#include "src/dipped.c"

/* - - -   BOOLEAN   - - - */

#define PROCEDURE	and_
#define NAME		"and"
#define OPER1		&
#define OPER2		&&
#include "src/andorxor.c"

#define PROCEDURE	or_
#define NAME		"or"
#define OPER1		|
#define OPER2		||
#include "src/andorxor.c"

#define PROCEDURE	xor_
#define NAME		"xor"
#define OPER1		^
#define OPER2		!=
#include "src/andorxor.c"

/* - - -   INTEGER   - - - */

#define PROCEDURE	ord_
#define NAME		"ord"
#define RESULTTYP	INTEGER_
#include "src/ordchr.c"

#define PROCEDURE	chr_
#define NAME		"chr"
#define RESULTTYP	CHAR_
#include "src/ordchr.c"

#include "src/abs.c"
#include "src/sign.c"
#include "src/neg.c"
#include "src/mul.c"
#include "src/divide.c"
#include "src/rem.c"
#include "src/div.c"
#include "src/strtol.c"
#include "src/strtod.c"
#include "src/format.c"
#include "src/formatf.c"

/* - - -   TIME   - - - */

#define PROCEDURE	localtime_
#define NAME		"localtime"
#define FUNC		localtime
#include "src/unmktime.c"

#define PROCEDURE	gmtime_
#define NAME		"gmtime"
#define FUNC		gmtime
#include "src/unmktime.c"

#include "src/decode.c"
#include "src/mktime.c"
#include "src/strftime.c"

/* - - -   FLOAT   - - - */

#define PROCEDURE	acos_
#define NAME		"acos"
#define FUNC		acos
#include "src/ufloat.c"

#define PROCEDURE	asin_
#define NAME		"asin"
#define FUNC		asin
#include "src/ufloat.c"

#define PROCEDURE	atan_
#define NAME		"atan"
#define FUNC		atan
#include "src/ufloat.c"

#define PROCEDURE	ceil_
#define NAME		"ceil"
#define FUNC		ceil
#include "src/ufloat.c"

#define PROCEDURE	cos_
#define NAME		"cos"
#define FUNC		cos
#include "src/ufloat.c"

#define PROCEDURE	cosh_
#define NAME		"cosh"
#define FUNC		cosh
#include "src/ufloat.c"

#define PROCEDURE	exp_
#define NAME		"exp"
#define FUNC		exp
#include "src/ufloat.c"

#define PROCEDURE	floor_
#define NAME		"floor"
#define FUNC		floor
#include "src/ufloat.c"

#define PROCEDURE	log_
#define NAME		"log"
#define FUNC		log
#include "src/ufloat.c"

#define PROCEDURE	log10_
#define NAME		"log10"
#define FUNC		log10
#include "src/ufloat.c"

#define PROCEDURE	sin_
#define NAME		"sin"
#define FUNC		sin
#include "src/ufloat.c"

#define PROCEDURE	sinh_
#define NAME		"sinh"
#define FUNC		sinh
#include "src/ufloat.c"

#define PROCEDURE	sqrt_
#define NAME		"sqrt"
#define FUNC		sqrt
#include "src/ufloat.c"

#define PROCEDURE	tan_
#define NAME		"tan"
#define FUNC		tan
#include "src/ufloat.c"

#define PROCEDURE	tanh_
#define NAME		"tanh"
#define FUNC		tanh
#include "src/ufloat.c"

#define PROCEDURE	atan2_
#define NAME		"atan2"
#define FUNC		atan2
#include "src/bfloat.c"

#define PROCEDURE	pow_
#define NAME		"pow"
#define FUNC		pow
#include "src/bfloat.c"

#include "src/frexp.c"
#include "src/modf.c"
#include "src/ldexp.c"
#include "src/trunc.c"

/* - - -   NUMERIC   - - - */

#define PROCEDURE	pred_
#define NAME		"pred"
#define OPER		-
#include "src/predsucc.c"

#define PROCEDURE	succ_
#define NAME		"succ"
#define OPER		+
#include "src/predsucc.c"

#define PROCEDURE	plus_
#define NAME		"+"
#define OPER		+
#include "src/plusminus.c"

#define PROCEDURE	minus_
#define NAME		"-"
#define OPER		-
#include "src/plusminus.c"

#define PROCEDURE	max_
#define NAME		"max"
#define OPER		<
#include "src/maxmin.c"

#define PROCEDURE	min_
#define NAME		"min"
#define OPER		>
#include "src/maxmin.c"

#include "src/compare.c"

#define PROCEDURE	eql_
#define NAME		"="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		==
#define SETCMP		i==j
#include "src/comprel.c"

#define PROCEDURE	neql_
#define NAME		"!="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		!=
#define SETCMP		i!=j
#include "src/comprel.c"

#define PROCEDURE	less_
#define NAME		"<"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<
#define SETCMP		i!=j&&!(i&~j)
#include "src/comprel.c"

#define PROCEDURE	leql_
#define NAME		"<="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		<=
#define SETCMP		!(i&~j)
#include "src/comprel.c"

#define PROCEDURE	greater_
#define NAME		">"
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>
#define SETCMP		i!=j&&!(j&~i)
#include "src/comprel.c"

#define PROCEDURE	geql_
#define NAME		">="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		>=
#define SETCMP		!(j&~i)
#include "src/comprel.c"

#define PROCEDURE	compare_
#define NAME		"compare"
#define CONSTRUCTOR	INTEGER_
#define OPR		+
#define SETCMP		i-j<0?-1:i-j>0
#include "src/comprel.c"

#include "src/sametype.c"

/* - - -   FILES AND STREAMS   - - - */

#include "src/fopen.c"
#include "src/fclose.c"
#include "src/fflush.c"
#include "src/fremove.c"
#include "src/frename.c"

#define PROCEDURE	feof_
#define NAME		"feof"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		(int)feof(stk->u.fil)
#include "src/fileget.c"

#define PROCEDURE	ferror_
#define NAME		"ferror"
#define CONSTRUCTOR	BOOLEAN_
#define EXPR		(int)ferror(stk->u.fil)
#include "src/fileget.c"

#define PROCEDURE	fgetch_
#define NAME		"fgetch"
#define CONSTRUCTOR	CHAR_
#define EXPR		fgetc(stk->u.fil)
#include "src/fileget.c"

#define PROCEDURE	ftell_
#define NAME		"ftell"
#define CONSTRUCTOR	INTEGER_
#define EXPR		(int)ftell(stk->u.fil)
#include "src/fileget.c"

PUSH_PROC(getch_, CHAR_, getchar())

#include "src/fgets.c"
#include "src/fput.c"
#include "src/fget.c"
#include "src/fputch.c"
#include "src/fputchars.c"
#include "src/fread.c"
#include "src/fwrite.c"
#include "src/fseek.c"

/* - - -   AGGREGATES   - - - */

#include "src/first.c"
#include "src/rest.c"
#include "src/uncons.c"
#include "src/unswons.c"
#include "src/equal.c"

#define PROCEDURE	in_
#define NAME		"in"
#define AGGR		stk
#define ELEM		stk->next
#include "src/inhas.c"

#define PROCEDURE	has_
#define NAME		"has"
#define AGGR		stk->next
#define ELEM		stk
#include "src/inhas.c"

#define PROCEDURE	of_
#define NAME		"of"
#define AGGR		stk
#define	INDEX		stk->next
#include "src/of_at.c"

#define PROCEDURE	at_
#define NAME		"at"
#define AGGR		stk->next
#define	INDEX		stk
#include "src/of_at.c"

#include "src/choice.c"
#include "src/case.c"
#include "src/opcase.c"

#define PROCEDURE	cons_
#define NAME		"cons"
#define AGGR		stk
#define ELEM		stk->next
#include "src/cons_swons.c"

#define PROCEDURE	swons_
#define NAME		"swons"
#define AGGR		stk->next
#define ELEM		stk
#include "src/cons_swons.c"

#include "src/drop.c"
#include "src/take.c"
#include "src/concat.c"
#include "src/enconcat.c"
#include "src/null.c"
#include "src/not.c"
#include "src/size.c"
#include "src/small.c"

#define PROCEDURE	integer_
#define NAME		"integer"
#define REL		==
#define TYP		INTEGER_
#include "src/type.c"

#define PROCEDURE	char_
#define NAME		"char"
#define REL		==
#define TYP		CHAR_
#include "src/type.c"

#define PROCEDURE	logical_
#define NAME		"logical"
#define REL		==
#define TYP		BOOLEAN_
#include "src/type.c"

#define PROCEDURE	string_
#define NAME		"string"
#define REL		==
#define TYP		STRING_
#include "src/type.c"

#define PROCEDURE	set_
#define NAME		"set"
#define REL		==
#define TYP		SET_
#include "src/type.c"

#define PROCEDURE	list_
#define NAME		"list"
#define REL		==
#define TYP		LIST_
#include "src/type.c"

#define PROCEDURE	leaf_
#define NAME		"leaf"
#define REL		!=
#define TYP		LIST_
#include "src/type.c"

#define PROCEDURE	float_
#define NAME		"float"
#define REL		==
#define TYP		FLOAT_
#include "src/type.c"

#define PROCEDURE	file_
#define NAME		"file"
#define REL		==
#define TYP		FILE_
#include "src/type.c"

#define PROCEDURE	user_
#define NAME		"user"
#define REL		==
#define TYP		USR_
#include "src/type.c"

#define USETOP(PROCEDURE,NAME,TYPE,BODY)			\
PRIVATE void PROCEDURE()					\
{ ONEPARAM(NAME); TYPE(NAME); BODY; POP(stk); }
USETOP(put_, "put", ONEPARAM, writefactor(stk, stdout); printf(" "))
USETOP(putch_, "putch", NUMERICTYPE, printf("%c", (int) stk->u.num))
USETOP(putchars_, "putchars", STRING, printf("%s", stk->u.str))
USETOP(setecho_, "setecho", NUMERICTYPE, echoflag = stk->u.num)
USETOP(setautoput_, "setautoput", NUMERICTYPE, autoput = stk->u.num)
USETOP(setundeferror_, "setundeferror", NUMERICTYPE, undeferror = stk->u.num)
USETOP(settracegc_, "settracegc", NUMERICTYPE, tracegc = stk->u.num)
USETOP(srand_, "srand", INTEGER, srand(stk->u.num))
USETOP(include_, "include", STRING, doinclude(stk->u.str))
USETOP(system_, "system", STRING, system(stk->u.str))

#include "src/undefs.c"
#include "src/argv.c"
#include "src/get.c"

#define PROCEDURE	help1_
#define REL		!=
#include "src/help.c"

#define PROCEDURE	h_help1_
#define REL		==
#include "src/help.c"

/* - - - - -   C O M B I N A T O R S   - - - - - */

#ifdef TRACE
PUBLIC void printfactor(Node *n, FILE *stm)
{
    switch (n->op) {
    case BOOLEAN_:
	fprintf(stm, "type boolean");
	return;
    case INTEGER_:
	fprintf(stm, "type integer");
	return;
    case FLOAT_:
	fprintf(stm, "type float");
	return;
    case SET_:
	fprintf(stm, "type set");
	return;
    case CHAR_:
	fprintf(stm, "type char");
	return;
    case STRING_:
	fprintf(stm, "type string");
	return;
    case LIST_:
	fprintf(stm, "type list");
	return;
    case USR_:
	fprintf(stm, n->u.ent->name);
	return;
    case FILE_:
	fprintf(stm, "type file");
	return;
    default:
	fprintf(stm, "%s", symtab[n->op].name);
	return;
    }
}
#endif

#ifdef TRACK_USED_SYMBOLS
static void report_symbols(void)
{
    Entry *n;

    for (n = symtab; n->name; n++)
	if (n->is_used)
	    fprintf(stderr, "%s\n", n->name);
}
#endif

void exeterm(Node *n)
{
#ifdef TRACK_USED_SYMBOLS
    static int first;

    if (!first) {
	first = 1;
	atexit(report_symbols);
    }
#endif
    while (n) {
#ifdef TRACE
	printfactor(n, stdout);
	printf(" . ");
	writeterm(stk, stdout);
	printf("\n");
#endif
	switch (n->op) {
	case COPIED_:
	case ILLEGAL_:
	    printf("exeterm: attempting to execute bad node\n");
	    break;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case FLOAT_:
	case SET_:
	case STRING_:
	case LIST_:
	    DUPLICATE(n);
	    break;
	case USR_:
	    if (!n->u.ent->u.body && undeferror)
		execerror("definition", n->u.ent->name);
	    if (!n->next) {
		n = n->u.ent->u.body;
		continue;
	    }
	    exeterm(n->u.ent->u.body);
	    break;
	default:
	    (*n->u.proc) ();
#ifdef TRACK_USED_SYMBOLS
	    symtab[(int) n->op].is_used = 1;
#endif
	    break;
	}
	n = n->next;
    }
}

#include "src/x.c"
#include "src/i.c"
#include "src/dip.c"

#define PROCEDURE	nullary_
#define NAME		"nullary"
#define PARAMCOUNT	ONEPARAM
#define TOP		stk
#include "src/n_ary.c"

#define PROCEDURE	unary_
#define NAME		"unary"
#define PARAMCOUNT	TWOPARAMS
#define TOP		stk->next
#include "src/n_ary.c"

#define PROCEDURE	binary_
#define NAME		"binary"
#define PARAMCOUNT	THREEPARAMS
#define TOP		stk->next->next
#include "src/n_ary.c"

#define PROCEDURE	ternary_
#define NAME		"ternary"
#define PARAMCOUNT	FOURPARAMS
#define TOP		stk->next->next->next
#include "src/n_ary.c"

#include "src/times.c"
#include "src/infra.c"
#include "src/app1.c"
#include "src/cleave.c"

PRIVATE void app11_()
{
    THREEPARAMS("app11");
    ONEQUOTE("app11");
    app1_();
    if (inside_condition || inside_critical)
	stk->next = stk->next->next;
/* XXX */
}

#include "src/unary2.c"
#include "src/unary3.c"
#include "src/unary4.c"

PRIVATE void app12_()
{
    THREEPARAMS("app12");
    unary2_();
    if (inside_condition || inside_critical)
	stk->next->next = stk->next->next->next;
/* XXX */
}

#include "src/map.c"
#include "src/step.c"
#include "src/fold.c"
#include "src/cond.c"

#define PROCEDURE	ifinteger_
#define NAME		"ifinteger"
#define TYP		INTEGER_
#include "src/if_type.c"

#define PROCEDURE	ifchar_
#define NAME		"ifchar"
#define TYP		CHAR_
#include "src/if_type.c"

#define PROCEDURE	iflogical_
#define NAME		"iflogical"
#define TYP		BOOLEAN_
#include "src/if_type.c"

#define PROCEDURE	ifstring_
#define NAME		"ifstring"
#define TYP		STRING_
#include "src/if_type.c"

#define PROCEDURE	ifset_
#define NAME		"ifset"
#define TYP		SET_
#include "src/if_type.c"

#define PROCEDURE	iffloat_
#define NAME		"iffloat"
#define TYP		FLOAT_
#include "src/if_type.c"

#define PROCEDURE	iffile_
#define NAME		"iffile"
#define TYP		FILE_
#include "src/if_type.c"

#define PROCEDURE	iflist_
#define NAME		"iflist"
#define TYP		LIST_
#include "src/if_type.c"

#include "src/filter.c"
#include "src/split.c"

#define PROCEDURE	some_
#define NAME		"some"
#define INITIAL		0
#include "src/someall.c"

#define PROCEDURE	all_
#define NAME		"all"
#define INITIAL		1
#include "src/someall.c"

#include "src/primrec.c"
#include "src/tailrec.c"
#include "src/construct.c"
#include "src/branch.c"
#include "src/while.c"
#include "src/ifte.c"
#include "src/condlinrec.c"
#include "src/condnestrec.c"
#include "src/linrec.c"
#include "src/binrec.c"
#include "src/treestep.c"
#include "src/treerec.c"
#include "src/genrec.c"
#include "src/treegenrec.c"

PRIVATE void plain_manual_()
{
    make_manual(0);
}

PRIVATE void html_manual_()
{
    make_manual(1);
}

PRIVATE void latex_manual_()
{
    make_manual(2);
}

PRIVATE void manual_list_aux_()
{
    manual_list_();
}

/* - - - - -   I N I T I A L I S A T I O N   - - - - - */

static struct {char *name; void (*proc) (); char *messg1, *messg2 ; }
    optable[] =
	/* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{

{"__ILLEGAL",		id_,		"->",
"internal error, cannot happen - supposedly."},

{"__COPIED",		id_,		"->",
"no message ever, used for gc."},

{"__USR",		id_,		"usg",
"user node."},

{"__ANON_FUNCT",	id_,		"->",
"op for anonymous function call."},

/* LITERALS */

{" truth value type",	id_,		"->  B",
"The logical type, or the type of truth values.\nIt has just two literals: true and false."},

{" character type",	id_,		"->  C",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed."},

{" integer type",	id_,		"->  I",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42."},

{" set type",		id_,		"->  {...}",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}."},

{" string type",	id_,		"->  \"...\" ",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted."},

{" list type",		id_,		"->  [...]",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *]."},

{" float type",		id_,		"->  F",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)"},

{" file type",		id_,		"->  FILE:",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr."},

/* OPERANDS */

{"false",		false_,		"->  false",
"Pushes the value false."},

{"true",		true_,		"->  true",
"Pushes the value true."},

{"maxint",		maxint_,	"->  maxint",
"Pushes largest integer (platform dependent). Typically it is 32 bits."},

{"setsize",		setsize_,	"->  setsize",
"Pushes the maximum number of elements in a set (platform dependent).\nTypically it is 32, and set members are in the range 0..31."},

{"stack",		stack_,		".. X Y Z  ->  .. X Y Z [Z Y X ..]",
"Pushes the stack as a list."},

{"__symtabmax",		symtabmax_,	"->  I",
"Pushes value of maximum size of the symbol table."},

{"__symtabindex",	symtabindex_,	"->  I",
"Pushes current size of the symbol table."},

{"__dump",		dump_,		"->  [..]",
"debugging only: pushes the dump as a list."},

{"conts",		conts_,		"->  [[P] [Q] ..]",
"Pushes current continuations. Buggy, do not use."},

{"autoput",		autoput_,	"->  I",
"Pushes current value of flag  for automatic output, I = 0..2."},

{"undeferror",		undeferror_,	"->  I",
"Pushes current value of undefined-is-error flag."},

{"undefs",		undefs_,	"->  [..]",
"Push a list of all undefined symbols in the current symbol table."},

{"echo",		echo_,		"->  I",
"Pushes value of echo flag, I = 0..3."},

{"clock",		clock_,		"->  I",
"Pushes the integer value of current CPU usage in milliseconds."},

{"time",		time_,		"->  I",
"Pushes the current time (in seconds since the Epoch)."},

{"rand",		rand_,		"->  I",
"I is a random integer."},

{"__memorymax",		memorymax_,	"->  I",
"Pushes value of total size of memory."},

{"stdin",		stdin_,		"->  S",
"Pushes the standard input stream."},

{"stdout",		stdout_,	"->  S",
"Pushes the standard output stream."},

{"stderr",		stderr_,	"->  S",
"Pushes the standard error stream."},


/* OPERATORS */

{"id",			id_,		"->",
"Identity function, does nothing.\nAny program of the form  P id Q  is equivalent to just  P Q."},

{"dup",			dup_,		"X  ->  X X",
"Pushes an extra copy of X onto stack."},

{"swap",		swap_,		"X Y  ->  Y X",
"Interchanges X and Y on top of the stack."},

{"rollup",              rollup_,        "X Y Z  ->  Z X Y",
"Moves X and Y up, moves Z down"},

{"rolldown",            rolldown_,      "X Y Z  ->  Y Z X",
"Moves Y and Z down, moves X up"},

{"rotate",              rotate_,        "X Y Z  ->  Z Y X",
"Interchanges X and Z"},

{"popd",                popd_,          "Y Z  ->  Z",
"As if defined by:   popd  ==  [pop] dip "},

{"dupd",                dupd_,          "Y Z  ->  Y Y Z",
"As if defined by:   dupd  ==  [dup] dip"},

{"swapd",               swapd_,         "X Y Z  ->  Y X Z",
"As if defined by:   swapd  ==  [swap] dip"},

{"rollupd",             rollupd_,       "X Y Z W  ->  Z X Y W",
"As if defined by:   rollupd  ==  [rollup] dip"},

{"rolldownd",           rolldownd_,     "X Y Z W  ->  Y Z X W",
"As if defined by:   rolldownd  ==  [rolldown] dip "},

{"rotated",             rotated_,       "X Y Z W  ->  Z Y X W",
"As if defined by:   rotated  ==  [rotate] dip"},

{"pop",			pop_,		"X  ->",
"Removes X from top of the stack."},

{"choice",		choice_,	"B T F  ->  X",
"If B is true, then X = T else X = F."},

{"or",			or_,		"X Y  ->  Z",
"Z is the union of sets X and Y, logical disjunction for truth values."},

{"xor",			xor_,		"X Y  ->  Z",
"Z is the symmetric difference of sets X and Y,\nlogical exclusive disjunction for truth values."},

{"and",			and_,		"X Y  ->  Z",
"Z is the intersection of sets X and Y, logical conjunction for truth values."},

{"not",			not_,		"X  ->  Y",
"Y is the complement of set X, logical negation for truth values."},

{"+",			plus_,		"M I  ->  N",
"Numeric N is the result of adding integer I to numeric M.\nAlso supports float."},

{"-",			minus_,		"M I  ->  N",
"Numeric N is the result of subtracting integer I from numeric M.\nAlso supports float."},

{"*",			mul_,		"I J  ->  K",
"Integer K is the product of integers I and J.  Also supports float."},

{"/",			divide_,	"I J  ->  K",
"Integer K is the (rounded) ratio of integers I and J.  Also supports float."},

{"rem",			rem_,		"I J  ->  K",
"Integer K is the remainder of dividing I by J.  Also supports float."},

{"div",			div_,		"I J  ->  K L",
"Integers K and L are the quotient and remainder of dividing I by J."},

{"sign",		sign_,		"N1  ->  N2",
"Integer N2 is the sign (-1 or 0 or +1) of integer N1,\nor float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1."},

{"neg",			neg_,		"I  ->  J",
"Integer J is the negative of integer I.  Also supports float."},

{"ord",			ord_,		"C  ->  I",
"Integer I is the Ascii value of character C (or logical or integer)."},

{"chr",			chr_,		"I  ->  C",
"C is the character whose Ascii value is integer I (or logical or character)."},

{"abs",			abs_,		"N1  ->  N2",
"Integer N2 is the absolute value (0,1,2..) of integer N1,\nor float N2 is the absolute value (0.0 ..) of float N1"},

{"acos",		acos_,		"F  ->  G",
"G is the arc cosine of F."},

{"asin",		asin_,		"F  ->  G",
"G is the arc sine of F."},

{"atan",		atan_,		"F  ->  G",
"G is the arc tangent of F."},

{"atan2",		atan2_,		"F G  ->  H",
"H is the arc tangent of F / G."},

{"ceil",		ceil_,		"F  ->  G",
"G is the float ceiling of F."},

{"cos",			cos_,		"F  ->  G",
"G is the cosine of F."},

{"cosh",		cosh_,		"F  ->  G",
"G is the hyperbolic cosine of F."},

{"exp",			exp_,		"F  ->  G",
"G is e (2.718281828...) raised to the Fth power."},

{"floor",		floor_,		"F  ->  G",
"G is the floor of F."},

{"frexp",		frexp_,		"F  ->  G I",
"G is the mantissa and I is the exponent of F.\nUnless F = 0, 0.5 <= abs(G) < 1.0."},

{"ldexp",		ldexp_,		"F I  ->  G",
"G is F times 2 to the Ith power."},

{"log",			log_,		"F  ->  G",
"G is the natural logarithm of F."},

{"log10",		log10_,		"F  ->  G",
"G is the common logarithm of F."},

{"modf",		modf_,		"F  ->  G H",
"G is the fractional part and H is the integer part\n(but expressed as a float) of F."},

{"pow",			pow_,		"F G  ->  H",
"H is F raised to the Gth power."},

{"sin",			sin_,		"F  ->  G",
"G is the sine of F."},

{"sinh",		sinh_,		"F  ->  G",
"G is the hyperbolic sine of F."},

{"sqrt",		sqrt_,		"F  ->  G",
"G is the square root of F."},

{"tan",			tan_,		"F  ->  G",
"G is the tangent of F."},

{"tanh",		tanh_,		"F  ->  G",
"G is the hyperbolic tangent of F."},

{"trunc",		trunc_,		"F  ->  I",
"I is an integer equal to the float F truncated toward zero."},

{"localtime",		localtime_,	"I  ->  T",
"Converts a time I into a list T representing local time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is a Boolean flagging daylight savings/summer time;\nweekday is 1 = Monday ... 7 = Sunday."},

{"gmtime",		gmtime_,	"I  ->  T",
"Converts a time I into a list T representing universal time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is false; weekday is 1 = Monday ... 7 = Sunday."},

{"mktime",		mktime_,	"T  ->  I",
"Converts a list T representing local time into a time I.\nT is in the format generated by localtime."},

{"strftime",		strftime_,	"T S1  ->  S2",
"Formats a list T in the format of localtime or gmtime\nusing string S1 and pushes the result S2."},

{"strtol",		strtol_,	"S I  ->  J",
"String S is converted to the integer J using base I.\nIf I = 0, assumes base 10,\nbut leading \"0\" means base 8 and leading \"0x\" means base 16."},

{"strtod",		strtod_,	"S  ->  R",
"String S is converted to the float R."},

{"format",		format_,	"N C I J  ->  S",
"S is the formatted version of N in mode C\n('d or 'i = decimal, 'o = octal, 'x or\n'X = hex with lower or upper case letters)\nwith maximum width I and minimum width J."},

{"formatf",		formatf_,	"F C I J  ->  S",
"S is the formatted version of F in mode C\n('e or 'E = exponential, 'f = fractional,\n'g or G = general with lower or upper case letters)\nwith maximum width I and precision J."},

{"srand",		srand_,		"I  ->",
"Sets the random integer seed to integer I."},

{"pred",		pred_,		"M  ->  N",
"Numeric N is the predecessor of numeric M."},

{"succ",		succ_,		"M  ->  N",
"Numeric N is the successor of numeric M."},

{"max",			max_,		"N1 N2  ->  N",
"N is the maximum of numeric values N1 and N2.  Also supports float."},

{"min",			min_,		"N1 N2  ->  N",
"N is the minimum of numeric values N1 and N2.  Also supports float."},

{"fclose",		fclose_,	"S  ->",
"Stream S is closed and removed from the stack."},

{"feof",		feof_,		"S  ->  S B",
"B is the end-of-file status of stream S."},

{"ferror",		ferror_,	"S  ->  S B",
"B is the error status of stream S."},

{"fflush",		fflush_,	"S  ->  S",
"Flush stream S, forcing all buffered output to be written."},

{"fget",		fget_,		"S  ->  S F",
"Reads a factor from stream S and pushes it onto stack."},

{"fgetch",		fgetch_,	"S  ->  S C",
"C is the next available character from stream S."},

{"fgets",		fgets_,		"S  ->  S L",
"L is the next available line (as a string) from stream S."},

{"fopen",		fopen_,		"P M  ->  S",
"The file system object with pathname P is opened with mode M (r, w, a, etc.)\nand stream object S is pushed; if the open fails, file:NULL is pushed."},

{"fread",		fread_,		"S I  ->  S L",
"I bytes are read from the current position of stream S\nand returned as a list of I integers."},

{"fwrite",		fwrite_,	"S L  ->  S",
"A list of integers are written as bytes to the current position of stream S."},

{"fremove",		fremove_,	"P  ->  B",
"The file system object with pathname P is removed from the file system.\nB is a boolean indicating success or failure."},

{"frename",		frename_,	"P1 P2  ->  B",
"The file system object with pathname P1 is renamed to P2.\nB is a boolean indicating success or failure."},

{"fput",		fput_,		"S X  ->  S",
"Writes X to stream S, pops X off stack."},

{"fputch",		fputch_,	"S C  ->  S",
"The character C is written to the current position of stream S."},

{"fputchars",		fputchars_,	"S \"abc..\"  ->  S",
"The string abc.. (no quotes) is written to the current position of stream S."},

{"fputstring",		fputchars_,	"S \"abc..\"  ->  S",
"== fputchars, as a temporary alternative."},

{"fseek",		fseek_,		"S P W  ->  S",
"Stream S is repositioned to position P relative to whence-point W,\nwhere W = 0, 1, 2 for beginning, current position, end respectively."},

{"ftell",		ftell_,		"S  ->  S I",
"I is the current position of stream S."},

{"unstack",		unstack_,	"[X Y ..]  ->  ..Y X",
"The list [X Y ..] becomes the new stack."},

{"cons",		cons_,		"X A  ->  B",
"Aggregate B is A with a new member X (first member for sequences)."},

{"swons",		swons_,		"A X  ->  B",
"Aggregate B is A with a new member X (first member for sequences)."},

{"first",		first_,		"A  ->  F",
"F is the first member of the non-empty aggregate A."},

{"rest",		rest_,		"A  ->  R",
"R is the non-empty aggregate A with its first member removed."},

{"compare",		compare_,	"A B  ->  I",
"I (=-1,0,+1) is the comparison of aggregates A and B.\nThe values correspond to the predicates <=, =, >=."},

{"at",			at_,		"A I  ->  X",
"X (= A[I]) is the member of A at position I."},

{"of",			of_,		"I A  ->  X",
"X (= A[I]) is the I-th member of aggregate A."},

{"size",		size_,		"A  ->  I",
"Integer I is the number of elements of aggregate A."},

{"opcase",		opcase_,	"X [..[X Xs]..]  ->  [Xs]",
"Indexing on type of X, returns the list [Xs]."},

{"case",		case_,		"X [..[X Y]..]  ->  Y i",
"Indexing on the value of X, execute the matching Y."},

{"uncons",		uncons_,	"A  ->  F R",
"F and R are the first and the rest of non-empty aggregate A."},

{"unswons",		unswons_,	"A  ->  R F",
"R and F are the rest and the first of non-empty aggregate A."},

{"drop",		drop_,		"A N  ->  B",
"Aggregate B is the result of deleting the first N elements of A."},

{"take",		take_,		"A N  ->  B",
"Aggregate B is the result of retaining just the first N elements of A."},

{"concat",		concat_,	"S T  ->  U",
"Sequence U is the concatenation of sequences S and T."},

{"enconcat",		enconcat_,	"X S T  ->  U",
"Sequence U is the concatenation of sequences S and T\nwith X inserted between S and T (== swapd cons concat)"},

{"name",		name_,		"sym  ->  \"sym\"",
"For operators and combinators, the string \"sym\" is the name of item sym,\nfor literals sym the result string is its type."},

{"intern",		intern_,	"\"sym\"  -> sym",
"Pushes the item whose name is \"sym\"."},

{"body",		body_,		"U  ->  [P]",
"Quotation [P] is the body of user-defined symbol U."},

/* PREDICATES */

{"null",		null_,		"X  ->  B",
"Tests for empty aggregate X or zero numeric."},

{"small",		small_,		"X  ->  B",
"Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1."},

{">=",			geql_,		"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than or equal to Y.  Also supports float."},

{">",			greater_,	"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than Y.  Also supports float."},

{"<=",			leql_,		"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than or equal to Y.  Also supports float."},

{"<",			less_,		"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than Y.  Also supports float."},

{"!=",			neql_,		"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X not equal to Y.  Also supports float."},

{"=",			eql_,		"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X equal to Y.  Also supports float."},

{"equal",		equal_,		"T U  ->  B",
"(Recursively) tests whether trees T and U are identical."},

{"has",			has_,		"A X  ->  B",
"Tests whether aggregate A has X as a member."},

{"in",			in_,		"X A  ->  B",
"Tests whether X is a member of aggregate A."},

{"sametype",		sametype_,	"X Y  ->  B",
"Tests whether X and Y have the same type."},

{"integer",		integer_,	"X  ->  B",
"Tests whether X is an integer."},

{"char",		char_,		"X  ->  B",
"Tests whether X is a character."},

{"logical",		logical_,	"X  ->  B",
"Tests whether X is a logical."},

{"set",			set_,		"X  ->  B",
"Tests whether X is a set."},

{"string",		string_,	"X  ->  B",
"Tests whether X is a string."},

{"list",		list_,		"X  ->  B",
"Tests whether X is a list."},

{"leaf",		leaf_,		"X  ->  B",
"Tests whether X is not a list."},

{"user",		user_,		"X  ->  B",
"Tests whether X is a user-defined symbol."},

{"float",		float_,		"R  ->  B",
"Tests whether R is a float."},

{"file",		file_,		"F  ->  B",
"Tests whether F is a file."},

/* COMBINATORS */

{"i",			i_,		"[P]  ->  ...",
"Executes P. So, [P] i  ==  P."},

{"x",			x_,		"[P] x  ->  ...",
"Executes P without popping [P]. So, [P] x  ==  [P] P."},

{"dip",			dip_,		"X [P]  ->  ... X",
"Saves X, executes P, pushes X back."},

{"app1",		app1_,		"X [P]  ->  R",
"Executes P, pushes result R on stack with X."},

{"app11",		app11_,		"X Y [P]  ->  R",
"Executes P, pushes result R on stack."},

{"app12",		app12_,		"X Y1 Y2 [P]  ->  R1 R2",
"Executes P twice, with Y1 and Y2, returns R1 and R2."},

{"construct",		construct_,	"[P] [[P1] [P2] ..]  ->  R1 R2 ..",
"Saves state of stack and then executes [P].\nThen executes each [Pi] to give Ri pushed onto saved stack."},

{"nullary",		nullary_,	"[P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes, none are removed from the stack."},

{"unary",		unary_,		"X [P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly one is removed from the stack."},

{"unary2",		unary2_,	"X1 X2 [P]  ->  R1 R2",
"Executes P twice, with X1 and X2 on top of the stack.\nReturns the two values R1 and R2."},

{"unary3",		unary3_,	"X1 X2 X3 [P]  ->  R1 R2 R3",
"Executes P three times, with Xi, returns Ri (i = 1..3)."},

{"unary4",		unary4_,	"X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4",
"Executes P four times, with Xi, returns Ri (i = 1..4)."},

{"app2",		unary2_,	"X1 X2 [P]  ->  R1 R2",
"Obsolescent.  == unary2"},

{"app3",		unary3_,	"X1 X2 X3 [P]  ->  R1 R2 R3",
"Obsolescent.  == unary3"},

{"app4",		unary4_,	"X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4",
"Obsolescent.  == unary4"},

{"binary",		binary_,	"X Y [P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly two are removed from the stack."},

{"ternary",		ternary_,	"X Y Z [P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly three are removed from the stack."},

{"cleave",		cleave_,	"X [P1] [P2]  ->  R1 R2",
"Executes P1 and P2, each with X on top, producing two results."},

{"branch",		branch_,	"B [T] [F]  ->  ...",
"If B is true, then executes T else executes F."},

{"ifte",		ifte_,		"[B] [T] [F]  ->  ...",
"Executes B. If that yields true, then executes T else executes F."},

{"ifinteger",		ifinteger_,	"X [T] [E]  ->  ...",
"If X is an integer, executes T else executes E."},

{"ifchar",		ifchar_,	"X [T] [E]  ->  ...",
"If X is a character, executes T else executes E."},

{"iflogical",		iflogical_,	"X [T] [E]  ->  ...",
"If X is a logical or truth value, executes T else executes E."},

{"ifset",		ifset_,		"X [T] [E]  ->  ...",
"If X is a set, executes T else executes E."},

{"ifstring",		ifstring_,	"X [T] [E]  ->  ...",
"If X is a string, executes T else executes E."},

{"iflist",		iflist_,	"X [T] [E]  ->  ...",
"If X is a list, executes T else executes E."},

{"iffloat",		iffloat_,	"X [T] [E]  ->  ...",
"If X is a float, executes T else executes E."},

{"iffile",		iffile_,	"X [T] [E]  ->  ...",
"If X is a file, executes T else executes E."},

{"cond",		cond_,		"[..[[Bi] Ti]..[D]]  ->  ...",
"Tries each Bi. If that yields true, then executes Ti and exits.\nIf no Bi yields true, executes default D."},

{"while",		while_,		"[B] [D]  ->  ...",
"While executing B yields true executes D."},

{"linrec",		linrec_,	"[P] [T] [R1] [R2]  ->  ...",
"Executes P. If that yields true, executes T.\nElse executes R1, recurses, executes R2."},

{"tailrec",		tailrec_,	"[P] [T] [R1]  ->  ...",
"Executes P. If that yields true, executes T.\nElse executes R1, recurses."},

{"binrec",		binrec_,	"[P] [T] [R1] [R2]  ->  ...",
"Executes P. If that yields true, executes T.\nElse uses R1 to produce two intermediates, recurses on both,\nthen executes R2 to combines their results."},

{"genrec",		genrec_,	"[B] [T] [R1] [R2]  ->  ...",
"Executes B, if that yields true executes T.\nElse executes R1 and then [[[B] [T] [R1] R2] genrec] R2."},

{"condnestrec",		condnestrec_,	"[ [C1] [C2] .. [D] ]  ->  ...",
"A generalisation of condlinrec.\nEach [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form\n[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].\nFor the case taken, executes each [Ri] but recurses between any two\nconsecutive [Ri]. (n > 3 would be exceptional.)"},

{"condlinrec",		condlinrec_,	"[ [C1] [C2] .. [D] ]  ->  ...",
"Each [Ci] is of the forms [[B] [T]] or [[B] [R1] [R2]].\nTries each B. If that yields true and there is just a [T], executes T and exit.\nIf there are [R1] and [R2], executes R1, recurses, executes R2.\nSubsequent cases are ignored. If no B yields true, then [D] is used.\nIt is then of the forms [[T]] or [[R1] [R2]]. For the former, executes T.\nFor the latter executes R1, recurses, executes R2."},

{"step",		step_,		"A [P]  ->  ...",
"Sequentially putting members of aggregate A onto stack,\nexecutes P for each member of A."},

{"fold",		fold_,		"A V0 [P]  ->  V",
"Starting with value V0, sequentially pushes members of aggregate A\nand combines with binary operator P to produce value V."},

{"map",			map_,		"A [P]  ->  B",
"Executes P on each member of aggregate A,\ncollects results in sametype aggregate B."},

{"times",		times_,		"N [P]  ->  ...",
"N times executes P."},

{"infra",		infra_,		"L1 [P]  ->  L2",
"Using list L1 as stack, executes P and returns a new list L2.\nThe first element of L1 is used as the top of stack,\nand after execution of P the top of stack becomes the first element of L2."},

{"primrec",		primrec_,	"X [I] [C]  ->  R",
"Executes I to obtain an initial value R0.\nFor integer X uses increasing positive integers to X, combines by C for new R.\nFor aggregate X uses successive members and combines by C for new R."},

{"filter",		filter_,	"A [B]  ->  A1",
"Uses test B to filter aggregate A producing sametype aggregate A1."},

{"split",		split_,		"A [B]  ->  A1 A2",
"Uses test B to split aggregate A into sametype aggregates A1 and A2 ."},

{"some",		some_,		"A [B]  ->  X",
"Applies test B to members of aggregate A, X = true if some pass."},

{"all",			all_,		"A [B]  ->  X",
"Applies test B to members of aggregate A, X = true if all pass."},

{"treestep",		treestep_,	"T [P]  ->  ...",
"Recursively traverses leaves of tree T, executes P for each leaf."},

{"treerec",		treerec_,	"T [O] [C]  ->  ...",
"T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C."},

{"treegenrec",		treegenrec_,	"T [O1] [O2] [C]  ->  ...",
"T is a tree. If T is a leaf, executes O1.\nElse executes O2 and then [[[O1] [O2] C] treegenrec] C."},

/* MISCELLANEOUS */

{"help",		help1_,		"->",
"Lists all defined symbols, including those from library files.\nThen lists all primitives of raw Joy\n(There is a variant: \"_help\" which lists hidden symbols)."},

{"_help",		h_help1_,	"->",
"Lists all hidden symbols in library and then all hidden inbuilt symbols."},

{"helpdetail",		helpdetail_,	"[ S1  S2  .. ]",
"Gives brief help on each symbol S in the list."},

{"manual",		plain_manual_,	"->",
"Writes this manual of all Joy primitives to output file."},

{"__html_manual",	html_manual_,	"->",
"Writes this manual of all Joy primitives to output file in HTML style."},

{"__latex_manual",	latex_manual_,	"->",
"Writes this manual of all Joy primitives to output file in Latex style but without the head and tail."},

{"__manual_list",	manual_list_aux_,	"->  L",
"Pushes a list L of lists (one per operator) of three documentation strings"},

{"__settracegc",	settracegc_,	"I  ->",
"Sets value of flag for tracing garbage collection to I (= 0..5)."},

{"setautoput",		setautoput_,	"I  ->",
"Sets value of flag for automatic put to I (if I = 0, none;\nif I = 1, put; if I = 2, stack)."},

{"setundeferror",	setundeferror_,	"I  ->",
"Sets flag that controls behavior of undefined functions\n(0 = no error, 1 = error)."},

{"setecho",		setecho_,	"I  ->",
"Sets value of echo flag for listing.\nI = 0: no echo, 1: echo, 2: with tab, 3: and linenumber."},

{"gc",			gc_,		"->",
"Initiates garbage collection."},

{"system",		system_,	"\"command\"  ->",
"Escapes to shell, executes string \"command\".\nThe string may cause execution of another program.\nWhen that has finished, the process returns to Joy."},

{"getenv",		getenv_,	"\"variable\"  ->  \"value\"",
"Retrieves the value of the environment variable \"variable\"."},

{"argv",		argv_,		"->  A",
"Creates an aggregate A containing the interpreter's command line arguments."},

{"argc",		argc_,		"->  I",
"Pushes the number of command line arguments. This is equivalent to 'argv size'."},

{"__memoryindex",	memoryindex_,	"->",
"Pushes current value of memory."},

{"get",			get_,		"->  F",
"Reads a factor from input and pushes it onto stack."},

{"getch",		getch_,		"->  F",
"Reads a character from input and pushes it onto stack."},

{"put",			put_,		"X  ->",
"Writes X to output, pops X off stack."},

{"putch",		putch_,		"N  ->",
"N : numeric, writes character whose ASCII is N."},

{"putchars",		putchars_,	"\"abc..\"  ->",
"Writes  abc.. (without quotes)"},

{"include",		include_,	"\"filnam.ext\"  ->",
"Transfers input to file whose name is \"filnam.ext\".\nOn end-of-file returns to previous input file."},

{"abort",		abortexecution_,"->",
"Aborts execution of current Joy program, returns to Joy main cycle."},

{"quit",		quit_,		"->",
"Exit from Joy."},

{0, id_, "->","->"}
};

#include "src/inisym.c"
#include "src/helpdetail.c"
#include "src/makemanual.c"
#include "src/manual.c"
#include "src/opername.c"

/* END of INTERP.C */
