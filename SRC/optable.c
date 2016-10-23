/*
    module  : optable.c
    version : 1.7
    date    : 10/21/16
*/
#include "interp.h"
#include "builtin.h"

struct optable_t optable[] =
	/* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{

{"__ILLEGAL",		id_,		"->",			" ",
"internal error, cannot happen - supposedly."},

{"__COPIED",		id_,		"->",			" ",
"no message ever, used for gc."},

{"__USR",		id_,		"->",			" ",
"user node."},

{"__ANON_FUNCT",	id_,		"->",			" ",
"op for anonymous function call."},

/* LITERALS */

{" truth value type",	id_,		"->  B",		" ",
"The logical type, or the type of truth values.\nIt has just two literals: true and false."},

{" character type",	id_,		"->  C",		" ",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed."},

{" integer type",	id_,		"->  I",		" ",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42."},

{" set type",		id_,		"->  {...}",		" ",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}."},

{" string type",	id_,		"->  \"...\" ",		" ",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted."},

{" list type",		id_,		"->  [...]",		" ",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *]."},

{" float type",		id_,		"->  F",		" ",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)"},

{" file type",		id_,		"->  FILE:",		" ",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr."},

/* OPERANDS */

{"false",		false_,		"->  false",		"A",
"Pushes the value false."},

{"true",		true_,		"->  true",		"A",
"Pushes the value true."},

{"maxint",		maxint_,	"->  maxint",		"A",
"Pushes largest integer (platform dependent). Typically it is 32 bits."},

{"setsize",		setsize_,	"->  setsize",		"A",
"Pushes the maximum number of elements in a set (platform dependent).\nTypically it is 32, and set members are in the range 0..31."},

{"stack",		stack_,		".. X Y Z  ->  .. X Y Z [Z Y X ..]",	"A",
"Pushes the stack as a list."},

{"__symtabmax",		__symtabmax_,	"->  I",		"A",
"Pushes value of maximum size of the symbol table."},

{"__symtabindex",	__symtabindex_,	"->  I",		"A",
"Pushes current size of the symbol table."},

{"__dump",		__dump_,	"->  [..]",		"A",
"debugging only: pushes the dump as a list."},

{"conts",		conts_,		"->  [[P] [Q] ..]",	"A",
"Pushes current continuations. Buggy, do not use."},

{"autoput",		autoput_,	"->  I",		"A",
"Pushes current value of flag  for automatic output, I = 0..2."},

{"undeferror",		undeferror_,	"->  I",		"A",
"Pushes current value of undefined-is-error flag."},

{"undefs",		undefs_,	"->  [..]",		"A",
"Push a list of all undefined symbols in the current symbol table."},

{"echo",		echo_,		"->  I",		"A",
"Pushes value of echo flag, I = 0..3."},

{"clock",		clock_,		"->  I",		"A",
"Pushes the integer value of current CPU usage in milliseconds."},

{"time",		time_,		"->  I",		"A",
"Pushes the current time (in seconds since the Epoch)."},

{"rand",		rand_,		"->  I",		"A",
"I is a random integer."},

{"__memorymax",		__memorymax_,	"->  I",		"A",
"Pushes value of total size of memory."},

{"stdin",		stdin_,		"->  S",		"A",
"Pushes the standard input stream."},

{"stdout",		stdout_,	"->  S",		"A",
"Pushes the standard output stream."},

{"stderr",		stderr_,	"->  S",		"A",
"Pushes the standard error stream."},

/* OPERATORS */

{"id",			id_,		"->",			" ",
"Identity function, does nothing.\nAny program of the form  P id Q  is equivalent to just  P Q."},

{"dup",			dup_,		"X  ->  X X",		"A",
"Pushes an extra copy of X onto stack."},

{"swap",		swap_,		"X Y  ->  Y X",		"DDAA",
"Interchanges X and Y on top of the stack."},

{"rollup",              rollup_,        "X Y Z  ->  Z X Y",	"DDDAAA",
"Moves X and Y up, moves Z down"},

{"rolldown",            rolldown_,      "X Y Z  ->  Y Z X",	"DDDAAA",
"Moves Y and Z down, moves X up"},

{"rotate",              rotate_,        "X Y Z  ->  Z Y X",	"DDDAAA",
"Interchanges X and Z"},

{"popd",                popd_,          "Y Z  ->  Z",		"DDA",
"As if defined by:   popd  ==  [pop] dip "},

{"dupd",                dupd_,          "Y Z  ->  Y Y Z",	"DDAAA",
"As if defined by:   dupd  ==  [dup] dip"},

{"swapd",               swapd_,         "X Y Z  ->  Y X Z",	"DDDAAA",
"As if defined by:   swapd  ==  [swap] dip"},

{"rollupd",             rollupd_,       "X Y Z W  ->  Z X Y W",	"DDDDAAAA",
"As if defined by:   rollupd  ==  [rollup] dip"},

{"rolldownd",           rolldownd_,     "X Y Z W  ->  Y Z X W",	"DDDDAAAA",
"As if defined by:   rolldownd  ==  [rolldown] dip "},

{"rotated",             rotated_,       "X Y Z W  ->  Z Y X W",	"DDDDAAAA",
"As if defined by:   rotated  ==  [rotate] dip"},

{"pop",			pop_,		"X  ->",		"D",
"Removes X from top of the stack."},

{"choice",		choice_,	"B T F  ->  X",		"DDDA",
"If B is true, then X = T else X = F."},

{"or",			or_,		"X Y  ->  Z",		"DDA",
"Z is the union of sets X and Y, logical disjunction for truth values."},

{"xor",			xor_,		"X Y  ->  Z",		"DDA",
"Z is the symmetric difference of sets X and Y,\nlogical exclusive disjunction for truth values."},

{"and",			and_,		"X Y  ->  Z",		"DDA",
"Z is the intersection of sets X and Y, logical conjunction for truth values."},

{"not",			not_,		"X  ->  Y",		"DA",
"Y is the complement of set X, logical negation for truth values."},

{"+",			plus_,		"M I  ->  N",		"DDA",
"Numeric N is the result of adding integer I to numeric M.\nAlso supports float."},

{"-",			minus_,		"M I  ->  N",		"DDA",
"Numeric N is the result of subtracting integer I from numeric M.\nAlso supports float."},

{"*",			mul_,		"I J  ->  K",		"DDA",
"Integer K is the product of integers I and J.  Also supports float."},

{"/",			divide_,	"I J  ->  K",		"DDA",
"Integer K is the (rounded) ratio of integers I and J.  Also supports float."},

{"rem",			rem_,		"I J  ->  K",		"DDA",
"Integer K is the remainder of dividing I by J.  Also supports float."},

{"div",			div_,		"I J  ->  K L",		"DDAA",
"Integers K and L are the quotient and remainder of dividing I by J."},

{"sign",		sign_,		"N1  ->  N2",		"DA",
"Integer N2 is the sign (-1 or 0 or +1) of integer N1,\nor float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1."},

{"neg",			neg_,		"I  ->  J",		"DA",
"Integer J is the negative of integer I.  Also supports float."},

{"ord",			ord_,		"C  ->  I",		"DA",
"Integer I is the Ascii value of character C (or logical or integer)."},

{"chr",			chr_,		"I  ->  C",		"DA",
"C is the character whose Ascii value is integer I (or logical or character)."},

{"abs",			abs_,		"N1  ->  N2",		"DA",
"Integer N2 is the absolute value (0,1,2..) of integer N1,\nor float N2 is the absolute value (0.0 ..) of float N1"},

{"acos",		acos_,		"F  ->  G",		"DA",
"G is the arc cosine of F."},

{"asin",		asin_,		"F  ->  G",		"DA",
"G is the arc sine of F."},

{"atan",		atan_,		"F  ->  G",		"DA",
"G is the arc tangent of F."},

{"atan2",		atan2_,		"F G  ->  H",		"DDA",
"H is the arc tangent of F / G."},

{"ceil",		ceil_,		"F  ->  G",		"DA",
"G is the float ceiling of F."},

{"cos",			cos_,		"F  ->  G",		"DA",
"G is the cosine of F."},

{"cosh",		cosh_,		"F  ->  G",		"DA",
"G is the hyperbolic cosine of F."},

{"exp",			exp_,		"F  ->  G",		"DA",
"G is e (2.718281828...) raised to the Fth power."},

{"floor",		floor_,		"F  ->  G",		"DA",
"G is the floor of F."},

{"round",		round_,		"F  ->  G",		"DA",
"G is F rounded to the nearest integer."},

{"frexp",		frexp_,		"F  ->  G I",		"DAA",
"G is the mantissa and I is the exponent of F.\nUnless F = 0, 0.5 <= abs(G) < 1.0."},

{"ldexp",		ldexp_,		"F I  ->  G",		"DDA",
"G is F times 2 to the Ith power."},

{"log",			log_,		"F  ->  G",		"DA",
"G is the natural logarithm of F."},

{"log10",		log10_,		"F  ->  G",		"DA",
"G is the common logarithm of F."},

{"modf",		modf_,		"F  ->  G H",		"DAA",
"G is the fractional part and H is the integer part\n(but expressed as a float) of F."},

{"pow",			pow_,		"F G  ->  H",		"DDA",
"H is F raised to the Gth power."},

{"sin",			sin_,		"F  ->  G",		"DA",
"G is the sine of F."},

{"sinh",		sinh_,		"F  ->  G",		"DA",
"G is the hyperbolic sine of F."},

{"sqrt",		sqrt_,		"F  ->  G",		"DA",
"G is the square root of F."},

{"tan",			tan_,		"F  ->  G",		"DA",
"G is the tangent of F."},

{"tanh",		tanh_,		"F  ->  G",		"DA",
"G is the hyperbolic tangent of F."},

{"trunc",		trunc_,		"F  ->  I",		"DA",
"I is an integer equal to the float F truncated toward zero."},

{"localtime",		localtime_,	"I  ->  T",		"DA",
"Converts a time I into a list T representing local time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is a Boolean flagging daylight savings/summer time;\nweekday is 1 = Monday ... 7 = Sunday."},

{"gmtime",		gmtime_,	"I  ->  T",		"DA",
"Converts a time I into a list T representing universal time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is false; weekday is 1 = Monday ... 7 = Sunday."},

{"mktime",		mktime_,	"T  ->  I",		"DA",
"Converts a list T representing local time into a time I.\nT is in the format generated by localtime."},

{"strftime",		strftime_,	"T S1  ->  S2",		"DDA",
"Formats a list T in the format of localtime or gmtime\nusing string S1 and pushes the result S2."},

{"strtol",		strtol_,	"S I  ->  J",		"DDA",
"String S is converted to the integer J using base I.\nIf I = 0, assumes base 10,\nbut leading \"0\" means base 8 and leading \"0x\" means base 16."},

{"strtod",		strtod_,	"S  ->  R",		"DA",
"String S is converted to the float R."},

{"format",		format_,	"N C I J  ->  S",	"DDDDA",
"S is the formatted version of N in mode C\n('d or 'i = decimal, 'o = octal, 'x or\n'X = hex with lower or upper case letters)\nwith maximum width I and minimum width J."},

{"formatf",		formatf_,	"F C I J  ->  S",	"DDDDA",
"S is the formatted version of F in mode C\n('e or 'E = exponential, 'f = fractional,\n'g or G = general with lower or upper case letters)\nwith maximum width I and precision J."},

{"srand",		srand_,		"I  ->",		"D",
"Sets the random integer seed to integer I."},

{"pred",		pred_,		"M  ->  N",		"DA",
"Numeric N is the predecessor of numeric M."},

{"succ",		succ_,		"M  ->  N",		"DA",
"Numeric N is the successor of numeric M."},

{"max",			max_,		"N1 N2  ->  N",		"DDA",
"N is the maximum of numeric values N1 and N2.  Also supports float."},

{"min",			min_,		"N1 N2  ->  N",		"DDA",
"N is the minimum of numeric values N1 and N2.  Also supports float."},

{"fclose",		fclose_,	"S  ->",		"D",
"Stream S is closed and removed from the stack."},

{"feof",		feof_,		"S  ->  S B",		"A",
"B is the end-of-file status of stream S."},

{"ferror",		ferror_,	"S  ->  S B",		"A",
"B is the error status of stream S."},

{"fflush",		fflush_,	"S  ->  S",		" ",
"Flush stream S, forcing all buffered output to be written."},

{"fget",		fget_,		"S  ->  S F",		"A",
"Reads a factor from stream S and pushes it onto stack."},

{"fgetch",		fgetch_,	"S  ->  S C",		"A",
"C is the next available character from stream S."},

{"fgets",		fgets_,		"S  ->  S L",		"A",
"L is the next available line (as a string) from stream S."},

{"fopen",		fopen_,		"P M  ->  S",		"DDA",
"The file system object with pathname P is opened with mode M (r, w, a, etc.)\nand stream object S is pushed; if the open fails, file:NULL is pushed."},

{"fread",		fread_,		"S I  ->  S L",		"DA",
"I bytes are read from the current position of stream S\nand returned as a list of I integers."},

{"fwrite",		fwrite_,	"S L  ->  S",		"D",
"A list of integers are written as bytes to the current position of stream S."},

{"fremove",		fremove_,	"P  ->  B",		"DA",
"The file system object with pathname P is removed from the file system.\nB is a boolean indicating success or failure."},

{"frename",		frename_,	"P1 P2  ->  B",		"DDA",
"The file system object with pathname P1 is renamed to P2.\nB is a boolean indicating success or failure."},

{"filetime",		filetime_,	"F  ->  T",		"DA",
"T is the modification time of file F."},

{"fput",		fput_,		"S X  ->  S",		"D",
"Writes X to stream S, pops X off stack."},

{"fputch",		fputch_,	"S C  ->  S",		"D",
"The character C is written to the current position of stream S."},

{"fputchars",		fputchars_,	"S \"abc..\"  ->  S",	"D",
"The string abc.. (no quotes) is written to the current position of stream S."},

{"fputstring",		fputchars_,	"S \"abc..\"  ->  S",	"D",
"== fputchars, as a temporary alternative."},

{"fseek",		fseek_,		"S P W  ->  S B",	"DDA",
"Stream S is repositioned to position P relative to whence-point W,\nwhere W = 0, 1, 2 for beginning, current position, end respectively."},

{"ftell",		ftell_,		"S  ->  S I",		"A",
"I is the current position of stream S."},

{"unstack",		unstack_,	"[X Y ..]  ->  ..Y X",	"?",
"The list [X Y ..] becomes the new stack."},

{"cons",		cons_,		"X A  ->  B",		"DDA",
"Aggregate B is A with a new member X (first member for sequences)."},

{"swons",		swons_,		"A X  ->  B",		"DDA",
"Aggregate B is A with a new member X (first member for sequences)."},

{"first",		first_,		"A  ->  F",		"DA",
"F is the first member of the non-empty aggregate A."},

{"rest",		rest_,		"A  ->  R",		"DA",
"R is the non-empty aggregate A with its first member removed."},

{"compare",		compare_,	"A B  ->  I",		"DDA",
"I (=-1,0,+1) is the comparison of aggregates A and B.\nThe values correspond to the predicates <=, =, >=."},

{"at",			at_,		"A I  ->  X",		"DDA",
"X (= A[I]) is the member of A at position I."},

{"of",			of_,		"I A  ->  X",		"DDA",
"X (= A[I]) is the I-th member of aggregate A."},

{"size",		size_,		"A  ->  I",		"DA",
"Integer I is the number of elements of aggregate A."},

{"opcase",		opcase_,	"X [..[X Xs]..]  ->  [Xs]",	"DDA",
"Indexing on type of X, returns the list [Xs]."},

{"case",		case_,		"X [..[X Y]..]  ->  Y i",	"DD?",
"Indexing on the value of X, execute the matching Y."},

{"uncons",		uncons_,	"A  ->  F R",		"DAA",
"F and R are the first and the rest of non-empty aggregate A."},

{"unswons",		unswons_,	"A  ->  R F",		"DAA",
"R and F are the rest and the first of non-empty aggregate A."},

{"drop",		drop_,		"A N  ->  B",		"DDA",
"Aggregate B is the result of deleting the first N elements of A."},

{"take",		take_,		"A N  ->  B",		"DDA",
"Aggregate B is the result of retaining just the first N elements of A."},

{"concat",		concat_,	"S T  ->  U",		"DDA",
"Sequence U is the concatenation of sequences S and T."},

{"enconcat",		enconcat_,	"X S T  ->  U",		"DDDA",
"Sequence U is the concatenation of sequences S and T\nwith X inserted between S and T (== swapd cons concat)"},

{"name",		name_,		"sym  ->  \"sym\"",	"DA",
"For operators and combinators, the string \"sym\" is the name of item sym,\nfor literals sym the result string is its type."},

{"intern",		intern_,	"\"sym\"  -> sym",	"DA",
"Pushes the item whose name is \"sym\"."},

{"body",		body_,		"U  ->  [P]",		"DA",
"Quotation [P] is the body of user-defined symbol U."},

/* PREDICATES */

{"null",		null_,		"X  ->  B",		"DA",
"Tests for empty aggregate X or zero numeric."},

{"small",		small_,		"X  ->  B",		"DA",
"Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1."},

{">=",			geql_,		"X Y  ->  B",		"DDA",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than or equal to Y.  Also supports float."},

{">",			greater_,	"X Y  ->  B",		"DDA",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than Y.  Also supports float."},

{"<=",			leql_,		"X Y  ->  B",		"DDA",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than or equal to Y.  Also supports float."},

{"<",			less_,		"X Y  ->  B",		"DDA",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than Y.  Also supports float."},

{"!=",			neql_,		"X Y  ->  B",		"DDA",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X not equal to Y.  Also supports float."},

{"=",			eql_,		"X Y  ->  B",		"DDA",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X equal to Y.  Also supports float."},

{"equal",		equal_,		"T U  ->  B",		"DDA",
"(Recursively) tests whether trees T and U are identical."},

{"has",			has_,		"A X  ->  B",		"DDA",
"Tests whether aggregate A has X as a member."},

{"in",			in_,		"X A  ->  B",		"DDA",
"Tests whether X is a member of aggregate A."},

{"sametype",		sametype_,	"X Y  ->  B",		"DDA",
"Tests whether X and Y have the same type."},

{"casting",		casting_,	"X Y  ->  Z",		"DDA",
"Z takes the value from X and the type from Y."},

{"integer",		integer_,	"X  ->  B",		"DA",
"Tests whether X is an integer."},

{"char",		char_,		"X  ->  B",		"DA",
"Tests whether X is a character."},

{"logical",		logical_,	"X  ->  B",		"DA",
"Tests whether X is a logical."},

{"set",			set_,		"X  ->  B",		"DA",
"Tests whether X is a set."},

{"string",		string_,	"X  ->  B",		"DA",
"Tests whether X is a string."},

{"list",		list_,		"X  ->  B",		"DA",
"Tests whether X is a list."},

{"leaf",		leaf_,		"X  ->  B",		"DA",
"Tests whether X is not a list."},

{"user",		user_,		"X  ->  B",		"DA",
"Tests whether X is a user-defined symbol."},

{"float",		float_,		"R  ->  B",		"DA",
"Tests whether R is a float."},

{"file",		file_,		"F  ->  B",		"DA",
"Tests whether F is a file."},

/* COMBINATORS */

{"i",			i_,		"[P]  ->  ...",		"D?",
"Executes P. So, [P] i  ==  P."},

{"x",			x_,		"[P] x  ->  ...",	"?",
"Executes P without popping [P]. So, [P] x  ==  [P] P."},

{"dip",			dip_,		"X [P]  ->  ... X",	"D?",
"Saves X, executes P, pushes X back."},

{"app1",		app1_,		"X [P]  ->  R",		"D?",
"Executes P, pushes result R on stack with X."},

{"app11",		app11_,		"X Y [P]  ->  R",	"DDDA",
"Executes P, pushes result R on stack."},

{"app12",		app12_,		"X Y1 Y2 [P]  ->  R1 R2",	"DDDDAA",
"Executes P twice, with Y1 and Y2, returns R1 and R2."},

{"construct",		construct_,	"[P] [[P1] [P2] ..]  ->  R1 R2 ..",	"DD?",
"Saves state of stack and then executes [P].\nThen executes each [Pi] to give Ri pushed onto saved stack."},

{"nullary",		nullary_,	"[P]  ->  R",		"DA",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes, none are removed from the stack."},

{"unary",		unary_,		"X [P]  ->  R",		"DDA",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly one is removed from the stack."},

{"unary2",		unary2_,	"X1 X2 [P]  ->  R1 R2",	"DDDAA",
"Executes P twice, with X1 and X2 on top of the stack.\nReturns the two values R1 and R2."},

{"unary3",		unary3_,	"X1 X2 X3 [P]  ->  R1 R2 R3",	"DDDDAAA",
"Executes P three times, with Xi, returns Ri (i = 1..3)."},

{"unary4",		unary4_,	"X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4",	"DDDDDAAAA",
"Executes P four times, with Xi, returns Ri (i = 1..4)."},

{"app2",		unary2_,	"X1 X2 [P]  ->  R1 R2",	"DDDAA",
"Obsolescent.  == unary2"},

{"app3",		unary3_,	"X1 X2 X3 [P]  ->  R1 R2 R3",	"DDDDAAA",
"Obsolescent.  == unary3"},

{"app4",		unary4_,	"X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4",	"DDDDDAAAA",
"Obsolescent.  == unary4"},

{"binary",		binary_,	"X Y [P]  ->  R",	"DDDA",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly two are removed from the stack."},

{"ternary",		ternary_,	"X Y Z [P]  ->  R",	"DDDDA",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly three are removed from the stack."},

{"cleave",		cleave_,	"X [P1] [P2]  ->  R1 R2",	"DDDAA",
"Executes P1 and P2, each with X on top, producing two results."},

{"branch",		branch_,	"B [T] [F]  ->  ...",	"DDD?",
"If B is true, then executes T else executes F."},

{"ifte",		ifte_,		"[B] [T] [F]  ->  ...",	"DDD?",
"Executes B. If that yields true, then executes T else executes F."},

{"ifinteger",		ifinteger_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is an integer, executes T else executes E."},

{"ifchar",		ifchar_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is a character, executes T else executes E."},

{"iflogical",		iflogical_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is a logical or truth value, executes T else executes E."},

{"ifset",		ifset_,		"X [T] [E]  ->  ...",	"DDD?",
"If X is a set, executes T else executes E."},

{"ifstring",		ifstring_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is a string, executes T else executes E."},

{"iflist",		iflist_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is a list, executes T else executes E."},

{"iffloat",		iffloat_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is a float, executes T else executes E."},

{"iffile",		iffile_,	"X [T] [E]  ->  ...",	"DDD?",
"If X is a file, executes T else executes E."},

{"cond",		cond_,		"[..[[Bi] Ti]..[D]]  ->  ...",	"D?",
"Tries each Bi. If that yields true, then executes Ti and exits.\nIf no Bi yields true, executes default D."},

{"while",		while_,		"[B] [D]  ->  ...",	"DDDA",
"While executing B yields true executes D."},

{"linrec",		linrec_,	"[P] [T] [R1] [R2]  ->  ...",	"DDDD?",
"Executes P. If that yields true, executes T.\nElse executes R1, recurses, executes R2."},

{"tailrec",		tailrec_,	"[P] [T] [R1]  ->  ...",	"DDD?",
"Executes P. If that yields true, executes T.\nElse executes R1, recurses."},

{"binrec",		binrec_,	"[P] [T] [R1] [R2]  ->  ...",	"DDDD?",
"Executes P. If that yields true, executes T.\nElse uses R1 to produce two intermediates, recurses on both,\nthen executes R2 to combines their results."},

{"genrec",		genrec_,	"[B] [T] [R1] [R2]  ->  ...",	"DDDD?",
"Executes B, if that yields true executes T.\nElse executes R1 and then [[[B] [T] [R1] R2] genrec] R2."},

{"condnestrec",		condnestrec_,	"[ [C1] [C2] .. [D] ]  ->  ...",	"DDA",
"A generalisation of condlinrec.\nEach [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form\n[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].\nFor the case taken, executes each [Ri] but recurses between any two\nconsecutive [Ri]. (n > 3 would be exceptional.)"},

{"condlinrec",		condlinrec_,	"[ [C1] [C2] .. [D] ]  ->  ...",	"DDA",
"Each [Ci] is of the forms [[B] [T]] or [[B] [R1] [R2]].\nTries each B. If that yields true and there is just a [T], executes T and exit.\nIf there are [R1] and [R2], executes R1, recurses, executes R2.\nSubsequent cases are ignored. If no B yields true, then [D] is used.\nIt is then of the forms [[T]] or [[R1] [R2]]. For the former, executes T.\nFor the latter executes R1, recurses, executes R2."},

{"step",		step_,		"A [P]  ->  ...",	"DD?",
"Sequentially putting members of aggregate A onto stack,\nexecutes P for each member of A."},

{"fold",		fold_,		"A V0 [P]  ->  V",	"DDDA",
"Starting with value V0, sequentially pushes members of aggregate A\nand combines with binary operator P to produce value V."},

{"map",			map_,		"A [P]  ->  B",		"DDA",
"Executes P on each member of aggregate A,\ncollects results in sametype aggregate B."},

{"times",		times_,		"N [P]  ->  ...",	"DDA",
"N times executes P."},

{"infra",		infra_,		"L1 [P]  ->  L2",	"DDA",
"Using list L1 as stack, executes P and returns a new list L2.\nThe first element of L1 is used as the top of stack,\nand after execution of P the top of stack becomes the first element of L2."},

{"primrec",		primrec_,	"X [I] [C]  ->  R",	"DDDA",
"Executes I to obtain an initial value R0.\nFor integer X uses increasing positive integers to X, combines by C for new R.\nFor aggregate X uses successive members and combines by C for new R."},

{"filter",		filter_,	"A [B]  ->  A1",	"DDA",
"Uses test B to filter aggregate A producing sametype aggregate A1."},

{"split",		split_,		"A [B]  ->  A1 A2",	"DDAA",
"Uses test B to split aggregate A into sametype aggregates A1 and A2 ."},

{"some",		some_,		"A [B]  ->  X",		"A",
"Applies test B to members of aggregate A, X = true if some pass."},

{"all",			all_,		"A [B]  ->  X",		"A",
"Applies test B to members of aggregate A, X = true if all pass."},

{"treestep",		treestep_,	"T [P]  ->  ...",	"DDDA",
"Recursively traverses leaves of tree T, executes P for each leaf."},

{"treerec",		treerec_,	"T [O] [C]  ->  ...",	"DDDA",
"T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C."},

{"treegenrec",		treegenrec_,	"T [O1] [O2] [C]  ->  ...",	"DDDDA",
"T is a tree. If T is a leaf, executes O1.\nElse executes O2 and then [[[O1] [O2] C] treegenrec] C."},

/* MISCELLANEOUS */

{"help",		help_,		"->",			" ",
"Lists all defined symbols, including those from library files.\nThen lists all primitives of raw Joy\n(There is a variant: \"_help\" which lists hidden symbols)."},

{"_help",		_help_,		"->",			" ",
"Lists all hidden symbols in library and then all hidden inbuilt symbols."},

{"helpdetail",		helpdetail_,	"[ S1  S2  .. ]",	"D",
"Gives brief help on each symbol S in the list."},

{"manual",		manual_,	"->",			" ",
"Writes this manual of all Joy primitives to output file."},

{"__html_manual",	__html_manual_,	"->",			" ",
"Writes this manual of all Joy primitives to output file in HTML style."},

{"__latex_manual",	__latex_manual_,"->",			" ",
"Writes this manual of all Joy primitives to output file in Latex style but without the head and tail."},

{"__manual_list",	__manual_list_,	"->  L",		"A",
"Pushes a list L of lists (one per operator) of three documentation strings"},

{"__settracegc",	__settracegc_,	"I  ->",		"D",
"Sets value of flag for tracing garbage collection to I (= 0..5)."},

{"setautoput",		setautoput_,	"I  ->",		"D",
"Sets value of flag for automatic put to I (if I = 0, none;\nif I = 1, put; if I = 2, stack)."},

{"setundeferror",	setundeferror_,	"I  ->",		"D",
"Sets flag that controls behavior of undefined functions\n(0 = no error, 1 = error)."},

{"setecho",		setecho_,	"I  ->",		"D",
"Sets value of echo flag for listing.\nI = 0: no echo, 1: echo, 2: with tab, 3: and linenumber."},

{"gc",			gc_,		"->",			" ",
"Initiates garbage collection."},

{"system",		system_,	"\"command\"  ->",	"D",
"Escapes to shell, executes string \"command\".\nThe string may cause execution of another program.\nWhen that has finished, the process returns to Joy."},

{"getenv",		getenv_,	"\"variable\"  ->  \"value\"",	"DA",
"Retrieves the value of the environment variable \"variable\"."},

{"argv",		argv_,		"->  A",		"A",
"Creates an aggregate A containing the interpreter's command line arguments."},

{"argc",		argc_,		"->  I",		"A",
"Pushes the number of command line arguments. This is equivalent to 'argv size'."},

{"__memoryindex",	__memoryindex_,	"->  I",		"A",
"Pushes current value of memory."},

{"get",			get_,		"->  F",		"A",
"Reads a factor from input and pushes it onto stack."},

{"getch",		getch_,		"->  F",		"A",
"Reads a character from input and pushes it onto stack."},

{"put",			put_,		"X  ->",		"D",
"Writes X to output, pops X off stack."},

{"putch",		putch_,		"N  ->",		"D",
"N : numeric, writes character whose ASCII is N."},

{"putchars",		putchars_,	"\"abc..\"  ->",	"D",
"Writes  abc.. (without quotes)"},

{"include",		include_,	"\"filnam.ext\"  ->",	"D",
"Transfers input to file whose name is \"filnam.ext\".\nOn end-of-file returns to previous input file."},

{"abort",		abort_,		"->",			" ",
"Aborts execution of current Joy program, returns to Joy main cycle."},

{"quit",		quit_,		"->",			" ",
"Exit from Joy."},

{0, id_, "->", " ", "->"}
};
