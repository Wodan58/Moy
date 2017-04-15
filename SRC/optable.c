/*
    module  : optable.c
    version : 1.10
    date    : 04/09/17
*/
#include "runtime.h"

STATIC struct optable_t optable[] = {
	/* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{"__ILLEGAL",		"->",
"internal error, cannot happen - supposedly."},

{"__COPIED",		"->",
"no message ever, used for gc."},

{"__USR",		"->",
"user node."},

{"__ANON_FUNCT",	"->",
"op for anonymous function call."},

/* LITERALS */

{" truth value type",	"->  B",
"The logical type, or the type of truth values.\nIt has just two literals: true and false."},

{" character type",	"->  C",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed."},

{" integer type",	"->  I",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42."},

{" set type",		"->  {...}",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}."},

{" string type",	"->  \"...\" ",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted."},

{" list type",		"->  [...]",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *]."},

{" float type",		"->  F",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2)"},

{" file type",		"->  FILE:",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr."},

/* OPERANDS */

{"nothing",		"->  false",
"Pushes the value nothing."},

{"false",		"->  false",
"Pushes the value false."},

{"true",		"->  true",
"Pushes the value true."},

{"maxint",		"->  maxint",
"Pushes largest integer (platform dependent). Typically it is 32 bits."},

{"setsize",		"->  setsize",
"Pushes the maximum number of elements in a set (platform dependent).\nTypically it is 32, and set members are in the range 0..31."},

{"stack",		".. X Y Z  ->  .. X Y Z [Z Y X ..]",
"Pushes the stack as a list."},

{"__symtabmax",		"->  I",
"Pushes value of maximum size of the symbol table."},

{"__symtabindex",	"->  I",
"Pushes current size of the symbol table."},

{"__dump",		"->  [..]",
"debugging only: pushes the dump as a list."},

{"conts",		"->  [[P] [Q] ..]",
"Pushes current continuations. Buggy, do not use."},

{"autoput",		"->  I",
"Pushes current value of flag  for automatic output, I = 0..2."},

{"undeferror",		"->  I",
"Pushes current value of undefined-is-error flag."},

{"undefs",		"->  [..]",
"Push a list of all undefined symbols in the current symbol table."},

{"echo",		"->  I",
"Pushes value of echo flag, I = 0..3."},

{"clock",		"->  I",
"Pushes the integer value of current CPU usage in milliseconds."},

{"time",		"->  I",
"Pushes the current time (in seconds since the Epoch)."},

{"rand",		"->  I",
"I is a random integer."},

{"__memorymax",		"->  I",
"Pushes value of total size of memory."},

{"stdin",		"->  S",
"Pushes the standard input stream."},

{"stdout",		"->  S",
"Pushes the standard output stream."},

{"stderr",		"->  S",
"Pushes the standard error stream."},

/* OPERATORS */

{"id",			"->",
"Identity function, does nothing.\nAny program of the form  P id Q  is equivalent to just  P Q."},

{"dup",			"X  ->  X X",
"Pushes an extra copy of X onto stack."},

{"swap",		"X Y  ->  Y X",
"Interchanges X and Y on top of the stack."},

{"rollup",              "X Y Z  ->  Z X Y",
"Moves X and Y up, moves Z down"},

{"rolldown",            "X Y Z  ->  Y Z X",
"Moves Y and Z down, moves X up"},

{"rotate",              "X Y Z  ->  Z Y X",
"Interchanges X and Z"},

{"popd",                "Y Z  ->  Z",
"As if defined by:   popd  ==  [pop] dip "},

{"dupd",                "Y Z  ->  Y Y Z",
"As if defined by:   dupd  ==  [dup] dip"},

{"swapd",               "X Y Z  ->  Y X Z",
"As if defined by:   swapd  ==  [swap] dip"},

{"rollupd",             "X Y Z W  ->  Z X Y W",
"As if defined by:   rollupd  ==  [rollup] dip"},

{"rolldownd",           "X Y Z W  ->  Y Z X W",
"As if defined by:   rolldownd  ==  [rolldown] dip "},

{"rotated",             "X Y Z W  ->  Z Y X W",
"As if defined by:   rotated  ==  [rotate] dip"},

{"pop",			"X  ->",
"Removes X from top of the stack."},

{"choice",		"B T F  ->  X",
"If B is true, then X = T else X = F."},

{"or",			"X Y  ->  Z",
"Z is the union of sets X and Y, logical disjunction for truth values."},

{"xor",			"X Y  ->  Z",
"Z is the symmetric difference of sets X and Y,\nlogical exclusive disjunction for truth values."},

{"and",			"X Y  ->  Z",
"Z is the intersection of sets X and Y, logical conjunction for truth values."},

{"not",			"X  ->  Y",
"Y is the complement of set X, logical negation for truth values."},

{"+",			"M I  ->  N",
"Numeric N is the result of adding integer I to numeric M.\nAlso supports float."},

{"-",			"M I  ->  N",
"Numeric N is the result of subtracting integer I from numeric M.\nAlso supports float."},

{"*",			"I J  ->  K",
"Integer K is the product of integers I and J.  Also supports float."},

{"/",			"I J  ->  K",
"Integer K is the (rounded) ratio of integers I and J.  Also supports float."},

{"rem",			"I J  ->  K",
"Integer K is the remainder of dividing I by J.  Also supports float."},

{"div",			"I J  ->  K L",
"Integers K and L are the quotient and remainder of dividing I by J."},

{"sign",		"N1  ->  N2",
"Integer N2 is the sign (-1 or 0 or +1) of integer N1,\nor float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1."},

{"neg",			"I  ->  J",
"Integer J is the negative of integer I.  Also supports float."},

{"ord",			"C  ->  I",
"Integer I is the Ascii value of character C (or logical or integer)."},

{"chr",			"I  ->  C",
"C is the character whose Ascii value is integer I (or logical or character)."},

{"abs",			"N1  ->  N2",
"Integer N2 is the absolute value (0,1,2..) of integer N1,\nor float N2 is the absolute value (0.0 ..) of float N1"},

{"acos",		"F  ->  G",
"G is the arc cosine of F."},

{"asin",		"F  ->  G",
"G is the arc sine of F."},

{"atan",		"F  ->  G",
"G is the arc tangent of F."},

{"atan2",		"F G  ->  H",
"H is the arc tangent of F / G."},

{"ceil",		"F  ->  G",
"G is the float ceiling of F."},

{"cos",			"F  ->  G",
"G is the cosine of F."},

{"cosh",		"F  ->  G",
"G is the hyperbolic cosine of F."},

{"exp",			"F  ->  G",
"G is e (2.718281828...) raised to the Fth power."},

{"floor",		"F  ->  G",
"G is the floor of F."},

{"round",		"F  ->  G",
"G is F rounded to the nearest integer."},

{"frexp",		"F  ->  G I",
"G is the mantissa and I is the exponent of F.\nUnless F = 0, 0.5 <= abs(G) < 1.0."},

{"ldexp",		"F I  ->  G",
"G is F times 2 to the Ith power."},

{"log",			"F  ->  G",
"G is the natural logarithm of F."},

{"log10",		"F  ->  G",
"G is the common logarithm of F."},

{"modf",		"F  ->  G H",
"G is the fractional part and H is the integer part\n(but expressed as a float) of F."},

{"pow",			"F G  ->  H",
"H is F raised to the Gth power."},

{"sin",			"F  ->  G",
"G is the sine of F."},

{"sinh",		"F  ->  G",
"G is the hyperbolic sine of F."},

{"sqrt",		"F  ->  G",
"G is the square root of F."},

{"tan",			"F  ->  G",
"G is the tangent of F."},

{"tanh",		"F  ->  G",
"G is the hyperbolic tangent of F."},

{"trunc",		"F  ->  I",
"I is an integer equal to the float F truncated toward zero."},

{"localtime",		"I  ->  T",
"Converts a time I into a list T representing local time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is a Boolean flagging daylight savings/summer time;\nweekday is 1 = Monday ... 7 = Sunday."},

{"gmtime",		"I  ->  T",
"Converts a time I into a list T representing universal time:\n[year month day hour minute second isdst yearday weekday].\nMonth is 1 = January ... 12 = December;\nisdst is false; weekday is 1 = Monday ... 7 = Sunday."},

{"mktime",		"T  ->  I",
"Converts a list T representing local time into a time I.\nT is in the format generated by localtime."},

{"strftime",		"T S1  ->  S2",
"Formats a list T in the format of localtime or gmtime\nusing string S1 and pushes the result S2."},

{"strtol",		"S I  ->  J",
"String S is converted to the integer J using base I.\nIf I = 0, assumes base 10,\nbut leading \"0\" means base 8 and leading \"0x\" means base 16."},

{"strtod",		"S  ->  R",
"String S is converted to the float R."},

{"format",		"N C I J  ->  S",
"S is the formatted version of N in mode C\n('d or 'i = decimal, 'o = octal, 'x or\n'X = hex with lower or upper case letters)\nwith maximum width I and minimum width J."},

{"formatf",		"F C I J  ->  S",
"S is the formatted version of F in mode C\n('e or 'E = exponential, 'f = fractional,\n'g or G = general with lower or upper case letters)\nwith maximum width I and precision J."},

{"srand",		"I  ->",
"Sets the random integer seed to integer I."},

{"pred",		"M  ->  N",
"Numeric N is the predecessor of numeric M."},

{"succ",		"M  ->  N",
"Numeric N is the successor of numeric M."},

{"max",			"N1 N2  ->  N",
"N is the maximum of numeric values N1 and N2.  Also supports float."},

{"min",			"N1 N2  ->  N",
"N is the minimum of numeric values N1 and N2.  Also supports float."},

{"fclose",		"S  ->",
"Stream S is closed and removed from the stack."},

{"feof",		"S  ->  S B",
"B is the end-of-file status of stream S."},

{"ferror",		"S  ->  S B",
"B is the error status of stream S."},

{"fflush",		"S  ->  S",
"Flush stream S, forcing all buffered output to be written."},

{"fget",		"S  ->  S F",
"Reads a factor from stream S and pushes it onto stack."},

{"fgetch",		"S  ->  S C",
"C is the next available character from stream S."},

{"fgets",		"S  ->  S L",
"L is the next available line (as a string) from stream S."},

{"fopen",		"P M  ->  S",
"The file system object with pathname P is opened with mode M (r, w, a, etc.)\nand stream object S is pushed; if the open fails, file:NULL is pushed."},

{"fread",		"S I  ->  S L",
"I bytes are read from the current position of stream S\nand returned as a list of I integers."},

{"fwrite",		"S L  ->  S",
"A list of integers are written as bytes to the current position of stream S."},

{"fremove",		"P  ->  B",
"The file system object with pathname P is removed from the file system.\nB is a boolean indicating success or failure."},

{"frename",		"P1 P2  ->  B",
"The file system object with pathname P1 is renamed to P2.\nB is a boolean indicating success or failure."},

{"filetime",		"F  ->  T",
"T is the modification time of file F."},

{"fput",		"S X  ->  S",
"Writes X to stream S, pops X off stack."},

{"fputch",		"S C  ->  S",
"The character C is written to the current position of stream S."},

{"fputchars",		"S \"abc..\"  ->  S",
"The string abc.. (no quotes) is written to the current position of stream S."},

{"fputstring",		"S \"abc..\"  ->  S",
"== fputchars, as a temporary alternative."},

{"fseek",		"S P W  ->  S B",
"Stream S is repositioned to position P relative to whence-point W,\nwhere W = 0, 1, 2 for beginning, current position, end respectively."},

{"ftell",		"S  ->  S I",
"I is the current position of stream S."},

{"unstack",		"[X Y ..]  ->  ..Y X",
"The list [X Y ..] becomes the new stack."},

{"cons",		"X A  ->  B",
"Aggregate B is A with a new member X (first member for sequences)."},

{"swons",		"A X  ->  B",
"Aggregate B is A with a new member X (first member for sequences)."},

{"first",		"A  ->  F",
"F is the first member of the non-empty aggregate A."},

{"rest",		"A  ->  R",
"R is the non-empty aggregate A with its first member removed."},

{"compare",		"A B  ->  I",
"I (=-1,0,+1) is the comparison of aggregates A and B.\nThe values correspond to the predicates <=, =, >=."},

{"index",		"X Y  ->  B",
"X (= A[I]) is the member of A at position I (I = 0,1)."},

{"at",			"A I  ->  X",
"X (= A[I]) is the member of A at position I."},

{"of",			"I A  ->  X",
"X (= A[I]) is the I-th member of aggregate A."},

{"size",		"A  ->  I",
"Integer I is the number of elements of aggregate A."},

{"casting",		"X Y  ->  Z",
"Z takes the value from X and the type from Y."},

{"opcase",		"X [..[X Xs]..]  ->  [Xs]",
"Indexing on type of X, returns the list [Xs]."},

{"case",		"X [..[X Y]..]  ->  Y i",
"Indexing on the value of X, execute the matching Y."},

{"uncons",		"A  ->  F R",
"F and R are the first and the rest of non-empty aggregate A."},

{"unswons",		"A  ->  R F",
"R and F are the rest and the first of non-empty aggregate A."},

{"drop",		"A N  ->  B",
"Aggregate B is the result of deleting the first N elements of A."},

{"take",		"A N  ->  B",
"Aggregate B is the result of retaining just the first N elements of A."},

{"concat",		"S T  ->  U",
"Sequence U is the concatenation of sequences S and T."},

{"enconcat",		"X S T  ->  U",
"Sequence U is the concatenation of sequences S and T\nwith X inserted between S and T (== swapd cons concat)"},

{"name",		"sym  ->  \"sym\"",
"For operators and combinators, the string \"sym\" is the name of item sym,\nfor literals sym the result string is its type."},

{"intern",		"\"sym\"  -> sym",
"Pushes the item whose name is \"sym\"."},

{"body",		"U  ->  [P]",
"Quotation [P] is the body of user-defined symbol U."},

/* PREDICATES */

{"null",		"X  ->  B",
"Tests for empty aggregate X or zero numeric."},

{"small",		"X  ->  B",
"Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1."},

{">=",			"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than or equal to Y.  Also supports float."},

{">",			"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X greater than Y.  Also supports float."},

{"<=",			"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than or equal to Y.  Also supports float."},

{"<",			"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X less than Y.  Also supports float."},

{"!=",			"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X not equal to Y.  Also supports float."},

{"=",			"X Y  ->  B",
"Either both X and Y are numeric or both are strings or symbols.\nTests whether X equal to Y.  Also supports float."},

{"equal",		"T U  ->  B",
"(Recursively) tests whether trees T and U are identical."},

{"has",			"A X  ->  B",
"Tests whether aggregate A has X as a member."},

{"in",			"X A  ->  B",
"Tests whether X is a member of aggregate A."},

{"sametype",		"X Y  ->  B",
"Tests whether X and Y have the same type."},

{"integer",		"X  ->  B",
"Tests whether X is an integer."},

{"char",		"X  ->  B",
"Tests whether X is a character."},

{"logical",		"X  ->  B",
"Tests whether X is a logical."},

{"set",			"X  ->  B",
"Tests whether X is a set."},

{"string",		"X  ->  B",
"Tests whether X is a string."},

{"list",		"X  ->  B",
"Tests whether X is a list."},

{"leaf",		"X  ->  B",
"Tests whether X is not a list."},

{"user",		"X  ->  B",
"Tests whether X is a user-defined symbol."},

{"float",		"R  ->  B",
"Tests whether R is a float."},

{"file",		"F  ->  B",
"Tests whether F is a file."},

/* COMBINATORS */

{"i",			"[P]  ->  ...",
"Executes P. So, [P] i  ==  P."},

{"x",			"[P] x  ->  ...",
"Executes P without popping [P]. So, [P] x  ==  [P] P."},

{"dip",			"X [P]  ->  ... X",
"Saves X, executes P, pushes X back."},

{"app1",		"X [P]  ->  R",
"Executes P, pushes result R on stack with X."},

{"app11",		"X Y [P]  ->  R",
"Executes P, pushes result R on stack."},

{"app12",		"X Y1 Y2 [P]  ->  R1 R2",
"Executes P twice, with Y1 and Y2, returns R1 and R2."},

{"construct",		"[P] [[P1] [P2] ..]  ->  R1 R2 ..",
"Saves state of stack and then executes [P].\nThen executes each [Pi] to give Ri pushed onto saved stack."},

{"nullary",		"[P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes, none are removed from the stack."},

{"unary",		"X [P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly one is removed from the stack."},

{"unary2",		"X1 X2 [P]  ->  R1 R2",
"Executes P twice, with X1 and X2 on top of the stack.\nReturns the two values R1 and R2."},

{"unary3",		"X1 X2 X3 [P]  ->  R1 R2 R3",
"Executes P three times, with Xi, returns Ri (i = 1..3)."},

{"unary4",		"X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4",
"Executes P four times, with Xi, returns Ri (i = 1..4)."},

{"app2",		"X1 X2 [P]  ->  R1 R2",
"Obsolescent.  == unary2"},

{"app3",		"X1 X2 X3 [P]  ->  R1 R2 R3",
"Obsolescent.  == unary3"},

{"app4",		"X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4",
"Obsolescent.  == unary4"},

{"binary",		"X Y [P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly two are removed from the stack."},

{"ternary",		"X Y Z [P]  ->  R",
"Executes P, which leaves R on top of the stack.\nNo matter how many parameters this consumes,\nexactly three are removed from the stack."},

{"cleave",		"X [P1] [P2]  ->  R1 R2",
"Executes P1 and P2, each with X on top, producing two results."},

{"branch",		"B [T] [F]  ->  ...",
"If B is true, then executes T else executes F."},

{"ifte",		"[B] [T] [F]  ->  ...",
"Executes B. If that yields true, then executes T else executes F."},

{"ifinteger",		"X [T] [E]  ->  ...",
"If X is an integer, executes T else executes E."},

{"ifchar",		"X [T] [E]  ->  ...",
"If X is a character, executes T else executes E."},

{"iflogical",		"X [T] [E]  ->  ...",
"If X is a logical or truth value, executes T else executes E."},

{"ifset",		"X [T] [E]  ->  ...",
"If X is a set, executes T else executes E."},

{"ifstring",		"X [T] [E]  ->  ...",
"If X is a string, executes T else executes E."},

{"iflist",		"X [T] [E]  ->  ...",
"If X is a list, executes T else executes E."},

{"iffloat",		"X [T] [E]  ->  ...",
"If X is a float, executes T else executes E."},

{"iffile",		"X [T] [E]  ->  ...",
"If X is a file, executes T else executes E."},

{"cond",		"[..[[Bi] Ti]..[D]]  ->  ...",
"Tries each Bi. If that yields true, then executes Ti and exits.\nIf no Bi yields true, executes default D."},

{"while",		"[B] [D]  ->  ...",
"While executing B yields true executes D."},

{"linrec",		"[P] [T] [R1] [R2]  ->  ...",
"Executes P. If that yields true, executes T.\nElse executes R1, recurses, executes R2."},

{"tailrec",		"[P] [T] [R1]  ->  ...",
"Executes P. If that yields true, executes T.\nElse executes R1, recurses."},

{"binrec",		"[P] [T] [R1] [R2]  ->  ...",
"Executes P. If that yields true, executes T.\nElse uses R1 to produce two intermediates, recurses on both,\nthen executes R2 to combines their results."},

{"genrec",		"[B] [T] [R1] [R2]  ->  ...",
"Executes B, if that yields true executes T.\nElse executes R1 and then [[[B] [T] [R1] R2] genrec] R2."},

{"condnestrec",		"[ [C1] [C2] .. [D] ]  ->  ...",
"A generalisation of condlinrec.\nEach [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form\n[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].\nFor the case taken, executes each [Ri] but recurses between any two\nconsecutive [Ri]. (n > 3 would be exceptional.)"},

{"condlinrec",		"[ [C1] [C2] .. [D] ]  ->  ...",
"Each [Ci] is of the forms [[B] [T]] or [[B] [R1] [R2]].\nTries each B. If that yields true and there is just a [T], executes T and exit.\nIf there are [R1] and [R2], executes R1, recurses, executes R2.\nSubsequent cases are ignored. If no B yields true, then [D] is used.\nIt is then of the forms [[T]] or [[R1] [R2]]. For the former, executes T.\nFor the latter executes R1, recurses, executes R2."},

{"step",		"A [P]  ->  ...",
"Sequentially putting members of aggregate A onto stack,\nexecutes P for each member of A."},

{"fold",		"A V0 [P]  ->  V",
"Starting with value V0, sequentially pushes members of aggregate A\nand combines with binary operator P to produce value V."},

{"map",			"A [P]  ->  B",
"Executes P on each member of aggregate A,\ncollects results in sametype aggregate B."},

{"times",		"N [P]  ->  ...",
"N times executes P."},

{"infra",		"L1 [P]  ->  L2",
"Using list L1 as stack, executes P and returns a new list L2.\nThe first element of L1 is used as the top of stack,\nand after execution of P the top of stack becomes the first element of L2."},

{"primrec",		"X [I] [C]  ->  R",
"Executes I to obtain an initial value R0.\nFor integer X uses increasing positive integers to X, combines by C for new R.\nFor aggregate X uses successive members and combines by C for new R."},

{"filter",		"A [B]  ->  A1",
"Uses test B to filter aggregate A producing sametype aggregate A1."},

{"split",		"A [B]  ->  A1 A2",
"Uses test B to split aggregate A into sametype aggregates A1 and A2 ."},

{"some",		"A [B]  ->  X",
"Applies test B to members of aggregate A, X = true if some pass."},

{"all",			"A [B]  ->  X",
"Applies test B to members of aggregate A, X = true if all pass."},

{"treestep",		"T [P]  ->  ...",
"Recursively traverses leaves of tree T, executes P for each leaf."},

{"treerec",		"T [O] [C]  ->  ...",
"T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C."},

{"treegenrec",		"T [O1] [O2] [C]  ->  ...",
"T is a tree. If T is a leaf, executes O1.\nElse executes O2 and then [[[O1] [O2] C] treegenrec] C."},

/* MISCELLANEOUS */

{"help",		"->",
"Lists all defined symbols, including those from library files.\nThen lists all primitives of raw Joy\n(There is a variant: \"_help\" which lists hidden symbols)."},

{"_help",		"->",
"Lists all hidden symbols in library and then all hidden inbuilt symbols."},

{"helpdetail",		"[ S1  S2  .. ]",
"Gives brief help on each symbol S in the list."},

{"manual",		"->",
"Writes this manual of all Joy primitives to output file."},

{"__html_manual",	"->",
"Writes this manual of all Joy primitives to output file in HTML style."},

{"__latex_manual",	"->",
"Writes this manual of all Joy primitives to output file in Latex style but without the head and tail."},

{"__manual_list",	"->  L",
"Pushes a list L of lists (one per operator) of three documentation strings"},

{"__settracegc",	"I  ->",
"Sets value of flag for tracing garbage collection to I (= 0..5)."},

{"setautoput",		"I  ->",
"Sets value of flag for automatic put to I (if I = 0, none;\nif I = 1, put; if I = 2, stack)."},

{"setundeferror",	"I  ->",
"Sets flag that controls behavior of undefined functions\n(0 = no error, 1 = error)."},

{"setecho",		"I  ->",
"Sets value of echo flag for listing.\nI = 0: no echo, 1: echo, 2: with tab, 3: and linenumber."},

{"gc",			"->",
"Initiates garbage collection."},

{"system",		"\"command\"  ->",
"Escapes to shell, executes string \"command\".\nThe string may cause execution of another program.\nWhen that has finished, the process returns to Joy."},

{"getenv",		"\"variable\"  ->  \"value\"",
"Retrieves the value of the environment variable \"variable\"."},

{"argv",		"->  A",
"Creates an aggregate A containing the interpreter's command line arguments."},

{"argc",		"->  I",
"Pushes the number of command line arguments. This is equivalent to 'argv size'."},

{"__memoryindex",	"->  I",
"Pushes current value of memory."},

{"get",			"->  F",
"Reads a factor from input and pushes it onto stack."},

{"getch",		"->  F",
"Reads a character from input and pushes it onto stack."},

{"put",			"X  ->",
"Writes X to output, pops X off stack."},

{"putch",		"N  ->",
"N : numeric, writes character whose ASCII is N."},

{"putchars",		"\"abc..\"  ->",
"Writes  abc.. (without quotes)"},

{"include",		"\"filnam.ext\"  ->",
"Transfers input to file whose name is \"filnam.ext\".\nOn end-of-file returns to previous input file."},

{"abort",		"->",
"Aborts execution of current Joy program, returns to Joy main cycle."},

{"quit",		"->",
"Exit from Joy."},

{0, "->", ""}
};
